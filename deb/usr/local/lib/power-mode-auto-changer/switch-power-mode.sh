#!/bin/bash
set -e

# Определяем активного пользователя (текущий сеанс)
ACTIVE_USER=$(loginctl list-sessions --no-legend | awk '{print $3}' | head -n1)
USER_CONFIG="/home/$ACTIVE_USER/.config/power-mode-auto-changer/power-modes.conf"

if [ ! -f "$USER_CONFIG" ]; then
    echo "Config not found: $USER_CONFIG"
    exit 1
fi
source "$USER_CONFIG"

STATE=$(cat "$AC_PATH")

if [ "$STATE" = "1" ]; then
    POWER_MODE="$ON_AC"
    NOTIFY_ICON="ac-adapter-symbolic"
else
    POWER_MODE="$ON_BATTERY"
    NOTIFY_ICON="battery-symbolic"
fi

case "$POWER_MODE" in
    "power-saver")
        NOTIFY_TEXT="Activated mode: Power saver"
        ;;
    "balanced")
        NOTIFY_TEXT="Activated mode: Balanced"
        ;;
    "performance")
        NOTIFY_TEXT="Activated mode: Performance"
        ;;
esac

powerprofilesctl set "$POWER_MODE"

ACTIVE_UID=$(id -u "$ACTIVE_USER")

DBUS_SESSION_BUS_ADDRESS="unix:path=/run/user/$ACTIVE_UID/bus"

sudo -u "$ACTIVE_USER" \
DBUS_SESSION_BUS_ADDRESS=$DBUS_SESSION_BUS_ADDRESS \
gdbus call --session \
  --dest org.Cinnamon \
  --object-path /org/Cinnamon \
  --method org.Cinnamon.ShowOSD \
  "{'icon': <'$NOTIFY_ICON'>, 'label': <'$NOTIFY_TEXT'>}"