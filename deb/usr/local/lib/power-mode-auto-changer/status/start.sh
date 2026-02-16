#!/bin/bash

USER_CONFIG=~/.config/power-mode-auto-changer/power-modes.conf

echo
echo "$STATUS_TEXT:"
echo "------------------------------"
cat $USER_CONFIG
if [ ! -f "$USER_CONFIG" ]; then
    echo "$STATUS_TEXT_APP_NOT_CONFIGURED:";
    echo "  power-mode-auto-changer --configure";
    echo
    exit 0
fi

source "$USER_CONFIG"

if systemctl --user is-enabled --quiet power-mode-auto-changer.service; then
    START_UP_AUTO_SYNC_STATUS=$STATUS_TEXT_ENABLED
else
    START_UP_AUTO_SYNC_STATUS=$STATUS_TEXT_DISABLED
fi

case "$ON_AC" in
    "power-saver")
        NOTIFY_TEXT_ON_AC=$CONFIGURATOR_TEXT_POWER_SAVER
        ;;
    "balanced")
        NOTIFY_TEXT_ON_AC=$CONFIGURATOR_TEXT_BALANCED
        ;;
    "performance")
        NOTIFY_TEXT_ON_AC=$CONFIGURATOR_TEXT_PERFORMANCE
        ;;
esac


case "$ON_BATTERY" in
    "power-saver")
        NOTIFY_TEXT_ON_BAT=$CONFIGURATOR_TEXT_POWER_SAVER
        ;;
    "balanced")
        NOTIFY_TEXT_ON_BAT=$CONFIGURATOR_TEXT_BALANCED
        ;;
    "performance")
        NOTIFY_TEXT_ON_BAT=$CONFIGURATOR_TEXT_PERFORMANCE
        ;;
esac

echo "$STATUS_TEXT_SYNC: $START_UP_AUTO_SYNC_STATUS"
echo "$STATUS_TEXT_ON_AC: $NOTIFY_TEXT_ON_AC"
echo "$STATUS_TEXT_ON_BAT: $NOTIFY_TEXT_ON_BAT"
echo
