#!/bin/bash
set -euo pipefail
DIR="AssetsExternal"
REMOTE="gdrive:proj-assets"
MANIFEST="asset_manifest.csv"

# マニフェスト生成
echo "path,size,sha256" > "$MANIFEST"
find "$DIR" -type f | while read -r f; do
  sz=$(stat -c%s "$f")
  sum=$(sha256sum "$f" | awk '{print $1}')
  echo "$f,$sz,$sum" >> "$MANIFEST"
done

# 同期
rclone sync "$DIR" "$REMOTE" --checksum

git add "$MANIFEST"
echo "更新: $MANIFEST をコミットしてください"
