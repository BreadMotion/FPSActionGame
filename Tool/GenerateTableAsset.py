import urllib.request
import sys
import unreal

# ===== 設定 =====
# CSV_URL = r"https://docs.google.com/spreadsheets/d/1YHssd98A2mBzEWdTSMbR_8xpO6EAnEMXHFCLLPs93_k/export?format=csv"
ROWSTRUCT_PATH = "/Script/FPSActionGame."
ASSET_FOLDER = "/Game/Data"


def fetch_csv(url: str, skip_lines: list[int] = None) -> str:
    """ "/edit?" 以降を探して置換"""
    url_edit = url.replace("/edit?usp=sharing", "/export?format=csv")
    """CSVを取得して指定行をスキップ"""
    with urllib.request.urlopen(url_edit) as resp:
        csv_str = resp.read().decode('utf-8-sig')

    if skip_lines:
        lines = csv_str.splitlines()
        for index in sorted(skip_lines, reverse=True):
            if 0 <= index < len(lines):
                del lines[index]
        csv_str = "\n".join(lines)

    return csv_str


def get_row_struct(path: str):
    """USTRUCTを取得"""
    row_struct = unreal.find_object(None, path)
    if not row_struct:
        raise RuntimeError(f"RowStructが見つかりません: {path}")
    return row_struct


def create_or_load_datatable(name: str, folder: str, row_struct) -> unreal.DataTable:
    """DataTableを作成または読み込み"""
    asset_tools = unreal.AssetToolsHelpers.get_asset_tools()
    asset_path = f"{folder}/{name}"
    asset = unreal.EditorAssetLibrary.load_asset(asset_path)

    if not asset:
        factory = unreal.DataTableFactory()
        factory.struct = row_struct
        asset = asset_tools.create_asset(name, folder, unreal.DataTable, factory)
        if not asset:
            raise RuntimeError(f"DataTable作成に失敗しました: {asset_path}")

    return asset


def fill_datatable_from_csv(asset: unreal.DataTable, csv_str: str):
    """DataTableにCSVを読み込む"""
    result = unreal.DataTableFunctionLibrary.fill_data_table_from_csv_string(asset, csv_str)
    if not result:
        raise RuntimeError("CSVの読み込みに失敗しました（型不整合・列名不一致など）")
    unreal.EditorAssetLibrary.save_loaded_asset(asset)


def main():
    csv_str = fetch_csv(sys.argv[1], skip_lines=[1, 2])  # 2,3行目を削除
    unreal.log(f"CSV取得成功:\n{csv_str}")

    row_struct = get_row_struct(ROWSTRUCT_PATH + sys.argv[2])
    datatable = create_or_load_datatable(sys.argv[3], ASSET_FOLDER, row_struct)
    fill_datatable_from_csv(datatable, csv_str)

    unreal.log(f"[OK] Updated DataTable: {ASSET_FOLDER}/{sys.argv[3]}")


if __name__ == "__main__":
    main()