#!/bin/bash

# --- Language detection logic ---
if [[ "$FORCED_LANG" == "ru" ]]; then
    LANG_SELECTED="ru"
elif [[ "$FORCED_LANG" == "en" ]]; then
    LANG_SELECTED="en"
else
    # Auto-detect from system locale
    SYS_LANG="${LC_MESSAGES:-$LANG}"
    SYS_LANG="${SYS_LANG%%.*}"   # remove .UTF-8

    if [[ "$SYS_LANG" == ru* ]]; then
        LANG_SELECTED="ru"
    else
        LANG_SELECTED="en"
    fi
fi