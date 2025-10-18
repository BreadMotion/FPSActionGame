@echo off
chcp 65001 >nul
setlocal

REM ===== 出力ファイル名 =====
set "OUTPUT_FILE=tree_filtered.txt"

REM ===== 古いログ削除 =====
if exist "%OUTPUT_FILE%" del "%OUTPUT_FILE%"

REM ===== 対象ディレクトリ設定 =====
set "TARGET_DIRS=Source Plugins"

REM ===== 出力開始 =====
echo [UE Project Tree Log] > "%OUTPUT_FILE%"
echo. >> "%OUTPUT_FILE%"

for %%D in (%TARGET_DIRS%) do (
    if exist "%%D" (
        echo ------------------------------ >> "%OUTPUT_FILE%"
        echo [%%D] >> "%OUTPUT_FILE%"
        echo ------------------------------ >> "%OUTPUT_FILE%"
        tree "%%D" /F /A | findstr /R /I /C:"^[^| ]" /C:"^[| ][+\\]" /C:".cs$" /C:".cpp$" /C:".h$" /C:".uplugin$" >> "%OUTPUT_FILE%"
        echo. >> "%OUTPUT_FILE%"
    ) else (
        echo [警告] %%D フォルダが存在しません >> "%OUTPUT_FILE%"
        echo. >> "%OUTPUT_FILE%"
    )
)

REM ===== 結果表示 =====
if exist "%OUTPUT_FILE%" (
    echo 出力完了: "%OUTPUT_FILE%"
    echo ------------------------------
    type "%OUTPUT_FILE%"
) else (
    echo [エラー] 出力ファイルが生成されませんでした。
)
echo ------------------------------
pause
