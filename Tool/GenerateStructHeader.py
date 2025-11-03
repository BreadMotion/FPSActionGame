# -*- coding: utf-8 -*-
import os
import csv
import re
import urllib.request
import sys
import unreal  # UEエディタ内で動かす前提

# ===== 設定 =====
# CSV_URL    = r"https://docs.google.com/spreadsheets/d/1YHssd98A2mBzEWdTSMbR_8xpO6EAnEMXHFCLLPs93_k/export?format=csv"
# STRUCT_NAME = "WeaponTable"
MODULE_API  = "FPSACTIONGAME_API"

PROJECT_DIR = unreal.Paths.project_dir()
OUT_HEADER  = os.path.join(PROJECT_DIR, "Source", "FPSActionGame", "Public", "Table")

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

# 各型のデフォルト初期値をマップ
DEFAULT_VALUE_MAP = {
    "int32": "0",
    "float": "0.0f",
    "double": "0.0",
    "bool": "false",
    "FName": "NAME_None",
    "FString": 'TEXT("")',
    "TSoftObjectPtr<UTexture2D>": "nullptr",
    "TSoftObjectPtr<USoundBase>": "nullptr",
}

def sanitize_identifier(s: str) -> str:
    """列名をC++の識別子に変換"""
    s = s.strip()
    s = re.sub(r'[^A-Za-z0-9_]', '_', s)
    if re.match(r'^[0-9]', s):
        s = '_' + s
    return s


def fetch_csv(url: str) -> list[list[str]]:
    """ "/edit?" 以降を探して置換"""
    url_edit = url.replace("/edit?usp=sharing", "/export?format=csv")
    """CSVを取得してリスト化"""
    with urllib.request.urlopen(url_edit) as resp:
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
    props = []
    for h, t, c in zip(headers[1:], types[1:], comment[1:]):
        default_value = DEFAULT_VALUE_MAP.get(t, "0")
        prop_code = (
            f'    // {c}\n'
            f'    UPROPERTY(EditAnywhere, BlueprintReadOnly)\n'
            f'    {t} {h} = {default_value};\n'
        )
        props.append(prop_code)

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


def write_header_file(path: str, code: str, fileName: str):
    """ヘッダーファイルに出力"""
    generate_path = path + "/" + fileName+".h"
    os.makedirs(os.path.dirname(generate_path), exist_ok=True)
    with open(generate_path, 'w', encoding='utf-8', newline='\n') as f:
        f.write(code)
    print(f"[OK] Generated: {generate_path}")


def main():
    rows = fetch_csv(sys.argv[1])
    headers, types, comment = parse_headers_and_types(rows)
    code = generate_struct_code(headers, types, comment, sys.argv[2], MODULE_API, sys.argv[1])
    write_header_file(OUT_HEADER, code, sys.argv[2])
    unreal.log(sys.argv)

if __name__ == "__main__":
    main()
