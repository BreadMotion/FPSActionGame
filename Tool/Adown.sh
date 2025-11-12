#!/bin/bash
set -euo pipefail
DIR="AssetsExternal"
REMOTE="gdrive:proj-assets"
rclone sync "$REMOTE" "$DIR" --checksum
