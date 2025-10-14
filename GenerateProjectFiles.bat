@echo off
chcp 932 >nul
cd /d %~dp0
setlocal ENABLEDELAYEDEXPANSION

echo ============================================
echo Unreal キャッシュ・ビルド中間ファイル削除中...
echo ============================================

REM --- 削除対象ディレクトリ ---
for %%d in (
    ".vs"
    "Binaries"
    "DerivedDataCache"
    "Intermediate"
    "Saved"
) do (
    if exist %%~d (
        echo 削除中: %%~d
        rmdir /s /q %%~d
    )
)

echo.
echo キャッシュ削除完了
echo.

REM --- .uproject の検索 ---
set "uproject="
for %%f in (*.uproject) do set "uproject=%%f"

if "%uproject%"=="" (
    echo .uproject ファイルが見つかりません。
    pause
    exit /b 1
)

echo.
echo プロジェクトファイルを再生成します...
echo 対象: %uproject%
echo ============================================

REM --- UnrealEditor.exe を検索して GenerateProjectFiles.bat のパスを取得 ---
set "UEPath="

for /d %%E in ("%ProgramFiles%\Epic Games\UE_*") do (
    if exist "%%E\Engine\Binaries\DotNET\UnrealBuildTool.exe" (
        set "UEPath=%%E\Engine\Binaries\DotNET\UnrealBuildTool.exe"
    )
)

if "%UEPath%"=="" (
    echo Unreal Engine のインストールが見つかりません。
    echo 手動で UnrealBuildTool.exe のパスを指定してください。
    pause
    exit /b 1
)

echo 使用パス: %UEPath%
echo.
echo GenerateProjectFiles を実行中...
echo.

"%UEPath%" -projectfiles "%cd%\%uproject%"

echo.
echo 完了しました。
pause
