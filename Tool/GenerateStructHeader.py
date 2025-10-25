# -*- coding: utf-8 -*-
import os
import csv
import re
import urllib.request
import unreal  # UEエディタ内で動かす前提

# ===== 設定 =====
CSV_URL    = r"https://docs.google.com/spreadsheets/d/1YHssd98A2mBzEWdTSMbR_8xpO6EAnEMXHFCLLPs93_k/export?format=csv"
STRUCT_NAME = "WeaponTable"
MODULE_API  = "FPSACTIONGAME_API"

PROJECT_DIR = unreal.Paths.project_dir()
OUT_HEADER  = os.path.join(PROJECT_DIR, "Source", "FPSActionGame", "Public", "Table", "WeaponTable.h")

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


def sanitize_identifier(s: str) -> str:
    """列名をC++の識別子に変換"""
    s = s.strip()
    s = re.sub(r'[^A-Za-z0-9_]', '_', s)
    if re.match(r'^[0-9]', s):
        s = '_' + s
    return s


def fetch_csv(url: str) -> list[list[str]]:
    """CSVを取得してリスト化"""
    with urllib.request.urlopen(url) as resp:
        raw = resp.read().decode('utf-8-sig')
    reader = list(csv.reader(raw.splitlines()))
    if len(reader) < 2:
        raise RuntimeError("CSVは少なくとも2行（ヘッダ/型行）が必要です。")
    return reader


def parse_headers_and_types(rows: list[list[str]]) -> tuple[list[str], list[str]]:
    """ヘッダと型行を解析してC++向けに変換"""
    headers = [sanitize_identifier(h) for h in rows[0]]
    types   = [TYPE_MAP.get(t.strip(), t.strip()) for t in rows[1]]

    # 先頭列はキー列としてFNameを採用
    if headers and headers[0].lower() in ("name", "rowname", "key", "(key)"):
        headers[0] = "Name"
        types[0] = "FName"

    return headers, types, rows[2]


def generate_struct_code(headers: list[str], types: list[str], comment: list[str], struct_name: str, module_api: str, csv_url: str) -> str:
    """USTRUCT用C++コードを生成"""
    props = [
        f'    // {c}\n'
        f'    UPROPERTY(EditAnywhere, BlueprintReadOnly) {t} {h};\n'
        for h, t, c in zip(headers[1:], types[1:], comment[1:])
    ]

    code = f'''#pragma once
#include "CoreMinimal.h"
#include "Engine/DataTable.h"

#include "{struct_name}.generated.h"

/**
 * @brief シートから自動生成されたDataTable行構造体
 * @details CSV: {csv_url}
 */
USTRUCT(BlueprintType)
struct {module_api} F{struct_name} : public FTableRowBase
{{
    GENERATED_BODY()

    /** DataTable行名 */
{os.linesep.join(props)}
}};
'''
    return code


def write_header_file(path: str, code: str):
    """ヘッダーファイルに出力"""
    os.makedirs(os.path.dirname(path), exist_ok=True)
    with open(path, 'w', encoding='utf-8', newline='\n') as f:
        f.write(code)
    print(f"[OK] Generated: {path}")


def main():
    rows = fetch_csv(CSV_URL)
    headers, types, comment = parse_headers_and_types(rows)
    code = generate_struct_code(headers, types, comment, STRUCT_NAME, MODULE_API, CSV_URL)
    write_header_file(OUT_HEADER, code)
    unreal.log("end")


if __name__ == "__main__":
    main()
