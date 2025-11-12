#!/bin/bash
set -euo pipefail
REMOTE="gdrive:proj-assets"
FILE="$1"
LOCKPATH="$REMOTE/.locks/${FILE}.lock"
rclone delete "$LOCKPATH" || true
echo "unlocked: $FILE"
