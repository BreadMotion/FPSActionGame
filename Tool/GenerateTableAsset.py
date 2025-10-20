import urllib.request
import unreal

# ===== 設定 =====
CSV_URL = r"https://docs.google.com/spreadsheets/d/1YHssd98A2mBzEWdTSMbR_8xpO6EAnEMXHFCLLPs93_k/edit?usp=drive_link?output=csv"
ROWSTRUCT_PATH = "/Script/FPSActionGame.WeaponTable" # ネイティブUSTRUCTのパス：/Script/<Module>.<Struct>
ASSET_NAME = "DT_Weapons" # 生成/更新するDataTable名
ASSET_FOLDER = "/Game/Data" # 保存フォルダ


# === CSV取得 ===
with urllib.request.urlopen(CSV_URL) as resp:
csv_str = resp.read().decode('utf-8-sig')


row_struct = unreal.find_object(None, ROWSTRUCT_PATH)
if not row_struct:
raise RuntimeError(f"RowStructが見つかりません: {ROWSTRUCT_PATH}")


# 既存DTがなければ作成
asset_tools = unreal.AssetToolsHelpers.get_asset_tools()
asset = unreal.EditorAssetLibrary.load_asset(f"{ASSET_FOLDER}/{ASSET_NAME}")
if not asset:
factory = unreal.DataTableFactory()
factory.row_struct = row_struct
asset = asset_tools.create_asset(ASSET_NAME, ASSET_FOLDER, unreal.DataTable, factory)
if not asset:
raise RuntimeError("DataTable作成に失敗しました")


# CSVで埋める（既存は上書き）
result = unreal.DataTableFunctionLibrary.fill_data_table_from_csv_string(asset, csv_str)
if not result:
raise RuntimeError("CSVの読み込みに失敗しました（型不整合・列名不一致など）")


unreal.EditorAssetLibrary.save_loaded_asset(asset)
print(f"[OK] Updated DataTable: {ASSET_FOLDER}/{ASSET_NAME}")