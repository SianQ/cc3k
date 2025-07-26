#!/bin/bash

# Rename all .h files to .cc files
for file in *.h; do
  # Check if any .h file exists
  [ -e "$file" ] || continue

  # Get the base name (remove .h extension)
  base="${file%.h}"

  # Rename the file
  mv "$file" "$base.cc"
  echo "Renamed: $file -> $base.cc"
done
