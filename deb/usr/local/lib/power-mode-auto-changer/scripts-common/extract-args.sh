#!/bin/bash

# --- Detect forced language parameter ---
FORCED_LANG=""

for arg in "$@"; do
    case "$arg" in
        --lang=*)
            FORCED_LANG="${arg#*=}"
            ;;
    esac
done