@echo off
:: --- UTF-8対応（文字化け防止） ---
chcp 65001 >nul
setlocal ENABLEDELAYEDEXPANSION

:: --- 対象フォルダ（1つ上の階層） ---
set "TargetDir=%~dp0.."
cd /d "%TargetDir%"

echo ============================================
echo Unreal Engine プロジェクト クリーンアップツール
echo ============================================
echo 対象ディレクトリ: %cd%
echo.

REM --- 一時ファイル削除 ---
for %%d in (
    ".vs"
    "Binaries"
    "DerivedDataCache"
    "Intermediate"
    "Saved"
) do (
    if exist %%~d (
        echo 削除中 : %%~d
        rmdir /s /q %%~d
    )
)

echo.
echo クリーンアップ完了！
echo.
pause 
