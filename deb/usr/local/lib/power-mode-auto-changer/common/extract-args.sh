#!/bin/bash

# --- Defaults ---
CURRENT_ACTION="status"
FORCED_LANG=""
ERROR_TYPE=""

ACTION_COUNT=0

for arg in "$@"; do
    case "$arg" in
        --lang=*)
            FORCED_LANG="${arg#*=}"
            ;;

        --help)
            CURRENT_ACTION="help"
            ((ACTION_COUNT++))
            ;;

        --version)
            CURRENT_ACTION="version"
            ((ACTION_COUNT++))
            ;;

        --configure)
            CURRENT_ACTION="configure"
            ((ACTION_COUNT++))
            ;;

        --status)
            CURRENT_ACTION="status"
            ((ACTION_COUNT++))
            ;;

        *)
            ERROR_TYPE="UNKNOWN_ARG=$arg"
            ;;
    esac
done

# --- Validate ---
# больше одного действия — ошибка
if [ "$ACTION_COUNT" -gt 1 ]; then
    ERROR_TYPE="MULTIPLE_ACTIONS"
fi
