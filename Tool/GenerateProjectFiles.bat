@echo off
:: --- UTF-8対応（文字化け防止） ---
chcp 65001 >nul
setlocal ENABLEDELAYEDEXPANSION

:: --- 対象フォルダ（1つ上の階層） ---
set "TargetDir=%~dp0.."
cd /d "%TargetDir%"

REM --- .uproject 検出 ---
set "uproject="
for %%f in (*.uproject) do set "uproject=%%f"

if "%uproject%"=="" (
    echo .uproject ファイルが見つかりません。
    pause
    exit /b 1
)

echo.
pause
