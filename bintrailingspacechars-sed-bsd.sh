#!/bin/sh

find . -iname '*.*pp' -type f -exec sed -i '' 's/[[:space:]]\{1,\}$//' {} \+
find . -iname '*.c' -type f -exec sed -i '' 's/[[:space:]]\{1,\}$//' {} \+
find . -iname '*.h' -type f -exec sed -i '' 's/[[:space:]]\{1,\}$//' {} \+
find . -iname '*.mm' -type f -exec sed -i '' 's/[[:space:]]\{1,\}$//' {} \+
find . -iname '*.txt' -type f -exec sed -i '' 's/[[:space:]]\{1,\}$//' {} \+
find . -iname '*.xml' -type f -exec sed -i '' 's/[[:space:]]\{1,\}$//' {} \+
