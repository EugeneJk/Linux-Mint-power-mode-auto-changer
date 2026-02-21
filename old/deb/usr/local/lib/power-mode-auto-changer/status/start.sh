#!/bin/bash

echo
echo "$STATUS_TEXT:"
echo "------------------------------"

if [ ! -f "$USER_CONFIG" ]; then
    echo "$STATUS_TEXT_APP_NOT_CONFIGURED:";
    echo "  power-mode-auto-changer --configure";
    echo
    exit 1
fi
MAIN_SCRIPTS_DIR="/usr/local/lib/power-mode-auto-changer"
COMMON_DIR="$MAIN_SCRIPTS_DIR/common"
source "$COMMON_DIR/user-config-validator.sh"

ACTIVE_USER=$(loginctl list-sessions --no-legend | awk '{print $3}' | head -n1)

if validate_user_config_file "$ACTIVE_USER" "$USER_CONFIG"; then
    echo "$STATUS_TEXT_CONFIG_IS_INVALID"
    exit 1
fi

source "$COMMON_DIR/parse-user-config.sh"
parse_user_config "$USER_CONFIG"

USER_TEXT_OVERRIDE_CONF="/home/$ACTIVE_USER/.config/power-mode-auto-changer/lang.conf"
if validate_user_config_file "$ACTIVE_USER" "$USER_TEXT_OVERRIDE_CONF"; then
    source "$COMMON_DIR/parse-user-text-override-config.sh"
    parse_user_text_override_config "$USER_TEXT_OVERRIDE_CONF"
else
    echo $STATUS_TEXT_LANGUAGE_OVERRIDE_IS_INVALID;
    exit 1
fi

if systemctl --user is-enabled --quiet $USER_SERVICE; then
    START_UP_AUTO_SYNC_STATUS=$STATUS_TEXT_ENABLED
    START_UP_AUTO_SYNC_COLOR=$GREEN
else
    START_UP_AUTO_SYNC_STATUS=$STATUS_TEXT_DISABLED
    START_UP_AUTO_SYNC_COLOR=$ORANGE
fi

case "$ON_AC" in
    "power-saver")
        NOTIFY_TEXT_ON_AC=$CONFIGURATOR_TEXT_POWER_SAVER
        ON_AC_COLOR=$ORANGE
        ;;
    "balanced")
        NOTIFY_TEXT_ON_AC=$CONFIGURATOR_TEXT_BALANCED
        ON_AC_COLOR=$GREEN
        ;;
    "performance")
        NOTIFY_TEXT_ON_AC=$CONFIGURATOR_TEXT_PERFORMANCE
        ON_AC_COLOR=$GREEN_BRIGHT
        ;;
esac


case "$ON_BATTERY" in
    "power-saver")
        NOTIFY_TEXT_ON_BAT=$CONFIGURATOR_TEXT_POWER_SAVER
        ON_BAT_COLOR=$GREEN
        ;;
    "balanced")
        NOTIFY_TEXT_ON_BAT=$CONFIGURATOR_TEXT_BALANCED
        ON_BAT_COLOR=$ORANGE
        ;;
    "performance")
        NOTIFY_TEXT_ON_BAT=$CONFIGURATOR_TEXT_PERFORMANCE
        ON_BAT_COLOR=$RED
        ;;
esac

echo -e "$STATUS_TEXT_SYNC: ${START_UP_AUTO_SYNC_COLOR}$START_UP_AUTO_SYNC_STATUS${RESET}"
echo -e "$STATUS_TEXT_ON_AC: ${ON_AC_COLOR}$NOTIFY_TEXT_ON_AC${RESET}"
echo -e "$STATUS_TEXT_ON_BAT: ${ON_BAT_COLOR}$NOTIFY_TEXT_ON_BAT${RESET}"
echo
