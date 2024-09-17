#!/usr/bin/env bash

mkdir -p examples

# {} means the file just found; \; means for every file
find . -type f -name "*.c" -exec mv {} examples/ \;

echo "Files correctly moved"

