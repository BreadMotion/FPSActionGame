@echo off
chcp 65001 >nul
setlocal

rem ==========================
rem 設定
rem ==========================
set "SCRIPT_DIR=%~dp0"
set "TARGET_DIR=%SCRIPT_DIR%..\\Saved\\Logs"
set "ZIP_FILE=%TEMP%\LogsUpload.zip"
set "UPLOAD_URL=https://discord.com/api/webhooks/1420300136600436736/4TjbLHxXo-Srk5tJtlGCtBcrNokfs__T-IWo8NmYlVfNbPpINgEd-dLGk7mg3DLAQAUl"

echo [1/5] 対象ディレクトリを確認中...
if not exist "%TARGET_DIR%" (
    echo [エラー] 対象ディレクトリが存在しません: %TARGET_DIR%
    pause
    exit /b 1
)

echo 対象: %TARGET_DIR%
echo.

rem ==========================
rem Gitユーザー名取得
rem ==========================
echo [2/5] Gitユーザー名を取得中...
for /f "delims=" %%a in ('git config user.name 2^>nul') do set "GIT_USER=%%a"

if not defined GIT_USER (
    echo Gitユーザー名が設定されていません。
    set /p "GIT_USER=手動で入力してください: "
)

echo ユーザー名: %GIT_USER%
echo.

rem ==========================
rem ZIP圧縮
rem ==========================
echo [3/5] 圧縮中...
powershell -Command "Compress-Archive -Path '%TARGET_DIR%\*' -DestinationPath '%ZIP_FILE%' -Force"
if not exist "%ZIP_FILE%" (
    echo [エラー] ZIPファイルの作成に失敗しました。
    pause
    exit /b 1
)
echo ZIP作成完了: %ZIP_FILE%
echo.

rem ==========================
rem 送信
rem ==========================
set "MESSAGE=%GIT_USER% から送信されました。"

echo [4/5] 送信中...
curl -X POST ^
    -F "content=%MESSAGE%" ^
    -F "file=@%ZIP_FILE%" ^
    "%UPLOAD_URL%"

if errorlevel 1 (
    echo [エラー] 送信に失敗しました。
    pause
    exit /b 1
)

echo 送信完了。
echo.

rem ==========================
rem 後処理
rem ==========================
echo [5/5] 一時ファイルを削除中...
del "%ZIP_FILE%" >nul 2>&1

echo すべての処理が完了しました。
pause
