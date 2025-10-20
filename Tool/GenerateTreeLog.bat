@echo off
chcp 65001 >nul
setlocal ENABLEDELAYEDEXPANSION

rem バッチの場所の1つ上のフォルダに移動
set "TargetDir=%~dp0.."
cd /d "%TargetDir%"

rem 出力ファイル設定
set "OUTPUT_FILE=Logs\tree_filtered.txt"
if exist "%OUTPUT_FILE%" del "%OUTPUT_FILE%"
if not exist "Logs" mkdir "Logs"

rem 対象ディレクトリリスト
set "TARGET_DIRS=Source Plugins"

echo [UE Project Tree Log] > "%OUTPUT_FILE%"
echo. >> "%OUTPUT_FILE%"

for %%D in (%TARGET_DIRS%) do (
    if exist "%%D" (
        echo ------------------------------ >> "%OUTPUT_FILE%"
        echo [%%D] >> "%OUTPUT_FILE%"
        echo ------------------------------ >> "%OUTPUT_FILE%"

        powershell -NoLogo -Command "Get-ChildItem -Recurse -Path '%%D' | ForEach-Object { if ($_.PSIsContainer) { Write-Output ($_.FullName.Substring($pwd.Path.Length+1) + '\') } elseif ($_.Extension -match '\.cpp$|\.h$|\.cs$|\.uplugin$') { Write-Output ('    ' + $_.FullName.Substring($pwd.Path.Length+1)) } }" >> "%OUTPUT_FILE%"
    )
)

echo 処理完了。結果は %OUTPUT_FILE% に出力されました。
pause
