#!/bin/bash
set -euo pipefail
REMOTE="gdrive:proj-assets"
FILE="$1"                 # 相対パス
LOCKPATH="$REMOTE/.locks/${FILE}.lock"
rclone copy /dev/null "$LOCKPATH" --metadata "owner=$(whoami)" || true
echo "locked: $FILE"
