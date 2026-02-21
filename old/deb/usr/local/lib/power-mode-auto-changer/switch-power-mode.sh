#!/bin/bash
set -e
MAIN_SCRIPTS_DIR="/usr/local/lib/power-mode-auto-changer"
SCRIPT_DIR="$MAIN_SCRIPTS_DIR/switch-power-mode"
COMMON_DIR="$MAIN_SCRIPTS_DIR/common"


# Add main variables 
source "$COMMON_DIR/main-vars.conf"
# Connect user config validator 
source "$COMMON_DIR/user-config-validator.sh"

if [ ! -f "$MAIN_CONFIG" ]; then
    exit 1
fi
source "$MAIN_CONFIG"


# Определяем активного пользователя (текущий сеанс)
ACTIVE_USER=$(loginctl list-sessions --no-legend | awk '{print $3}' | head -n1)

# Read user config
USER_CONFIG="/home/$ACTIVE_USER/.config/power-mode-auto-changer/$USER_CONFIG_FILE"

if ! validate_user_config_file "$ACTIVE_USER" "$USER_CONFIG"; then
    exit 1
fi

source "$COMMON_DIR/parse-user-config.sh"
parse_user_config "$USER_CONFIG"

# Reading AC state
STATE=$(cat "$AC_PATH")

if [ "$STATE" = "1" ]; then
    POWER_MODE="$ON_AC"
    NOTIFY_ICON="ac-adapter-symbolic"
else
    POWER_MODE="$ON_BATTERY"
    NOTIFY_ICON="battery-symbolic"
fi

CURRENT_MODE="$(powerprofilesctl get 2>/dev/null)"

if [[ "${CURRENT_MODE}" == "${POWER_MODE}" ]]; then
    exit 0
fi


#connect translations 
LANG_FILE="$COMMON_DIR/lang/$NOTIFY_LANG.conf"

if [ ! -f "$LANG_FILE" ]; then
    exit 1
fi
source "$LANG_FILE"

USER_TEXT_OVERRIDE_CONF="/home/$ACTIVE_USER/.config/power-mode-auto-changer/lang.conf"
if validate_user_config_file "$ACTIVE_USER" "$USER_TEXT_OVERRIDE_CONF"; then
    source "$COMMON_DIR/parse-user-text-override-config.sh"
    parse_user_text_override_config "$USER_TEXT_OVERRIDE_CONF"
fi

case "$POWER_MODE" in
    "power-saver")
        NOTIFY_TEXT="${CUSTOM_TEXT_POWER_SAVER:-$CONFIGURATOR_TEXT_POWER_SAVER}"
        ;;
    "balanced")
        NOTIFY_TEXT="${CUSTOM_TEXT_BALANCED:-$CONFIGURATOR_TEXT_BALANCED}"
        ;;
    "performance")
        NOTIFY_TEXT="${CUSTOM_TEXT_PERFORMANCE:-$CONFIGURATOR_TEXT_PERFORMANCE}"
        ;;
    *)
        exit 1
        ;;
esac

powerprofilesctl set "$POWER_MODE"

# connect show_notification function
source "$SCRIPT_DIR/show-notification.sh"

show_notification "$ACTIVE_USER" "$NOTIFY_ICON" "$NOTIFY_TEXT"
