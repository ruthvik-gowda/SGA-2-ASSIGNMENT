#!/bin/bash

SOURCE="submissions"
BACKUP="backup"
REPORT="report.txt"
ERRORS="errors.log"

mkdir -p "$BACKUP" 2>>"$ERRORS"

total=0
duplicates=0
backed_up=0

declare -A hashes

for file in "$SOURCE"/*; do
    if [ -f "$file" ]; then
        ((total++))
        hash=$(sha256sum "$file" 2>>"$ERRORS" | awk '{print $1}')

        if [[ -n "${hashes[$hash]}" ]]; then
            ((duplicates++))
        else
            hashes[$hash]=1
            cp "$file" "$BACKUP"/ 2>>"$ERRORS"
            ((backed_up++))
        fi
    fi
done

echo "Files processed: $total" > "$REPORT"
echo "Duplicate files: $duplicates" >> "$REPORT"
echo "Files backed up: $backed_up" >> "$REPORT"
