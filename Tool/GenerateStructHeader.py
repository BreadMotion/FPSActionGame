# -*- coding: utf-8 -*-
import os, csv, re, urllib.request
import unreal  # UEエディタ内で動かす前提（プロジェクトルート取得用）

# ===== 設定 =====
# Googleスプレッドシートは「ウェブに公開」して ?output=csv のURLを使う
CSV_URL = r"https://docs.google.com/spreadsheets/d/1YHssd98A2mBzEWdTSMbR_8xpO6EAnEMXHFCLLPs93_k/edit?usp=drive_link?output=csv"
STRUCT_NAME = "FWeaponTable"            # 生成するUSTRUCT名
MODULE_API  = "FPSACTIONGAME_API"       # モジュールAPIマクロ

# 出力先（プロジェクト直下からの絶対パスを生成）
PROJECT_DIR = unreal.Paths.project_dir()  # 例: D:/Working/UnityProjects/FPSActionGame/
OUT_HEADER  = os.path.join(PROJECT_DIR, "Source", "FPSActionGame", "Public", "Table", "WeaponTable.generated.h")

# CSVの型→C++型マップ（必要に応じて追加）
TYPE_MAP = {
    "int": "int32",
    "int32": "int32",
    "float": "float",
    "double": "double",
    "bool": "bool",
    "name": "FName",
    "string": "FString",
    "FString": "FString",
    "FName": "FName",
    "TSoftObjectPtr<UTexture2D>": "TSoftObjectPtr<UTexture2D>",
    "TSoftObjectPtr<USoundBase>": "TSoftObjectPtr<USoundBase>",
}

def _sanitize_identifier(s: str) -> str:
    s = s.strip()
    s = re.sub(r'[^A-Za-z0-9_]', '_', s)
    if re.match(r'^[0-9]', s):
        s = '_' + s
    return s

# === CSVダウンロード → メモリ読込 ===
with urllib.request.urlopen(CSV_URL) as resp:
    raw = resp.read().decode('utf-8-sig')

rows = list(csv.reader(raw.splitlines()))
if len(rows) < 2:
    raise RuntimeError("CSVは少なくとも2行（ヘッダ/型行）が必要です。")

headers = [_sanitize_identifier(h) for h in rows[0]]
types   = [TYPE_MAP.get(t.strip(), t.strip()) for t in rows[1]]

# 先頭列はキー列としてFNameを採用
if headers and headers[0].lower() in ("name", "rowname", "key", "(key)"):
    headers[0] = "Name"
    types[0]   = "FName"

# UPROPERTY列の整形（Name以外）
props = []
for h, t in zip(headers[1:], types[1:]):
    props.append(f'    UPROPERTY(EditAnywhere, BlueprintReadOnly) {t} {h};')

code = f'''#pragma once
#include "CoreMinimal.h"
#include "Engine/DataTable.h"

/**
 * @brief シートから自動生成されたDataTable行構造体
 * @details CSV: {CSV_URL}
 */
USTRUCT(BlueprintType)
struct {MODULE_API} {STRUCT_NAME} : public FTableRowBase
{{
    GENERATED_BODY()

    /** DataTable行名（CSVの1列目） */
    UPROPERTY(EditAnywhere, BlueprintReadOnly) FName Name;
{os.linesep.join(props)}
}};
'''

os.makedirs(os.path.dirname(OUT_HEADER), exist_ok=True)
with open(OUT_HEADER, 'w', encoding='utf-8') as out:
    out.write(code)

print(f"[OK] Generated: {OUT_HEADER}")
