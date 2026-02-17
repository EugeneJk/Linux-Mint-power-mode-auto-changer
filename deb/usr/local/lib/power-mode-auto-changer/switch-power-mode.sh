#!/bin/bash
set -e
MAIN_SCRIPTS_DIR="/usr/local/lib/power-mode-auto-changer"

# Add main variables 
source "$MAIN_SCRIPTS_DIR/common/main-vars.conf"

if [ ! -f "$MAIN_CONFIG" ]; then
    exit 1
fi
source "$MAIN_CONFIG"


# Определяем активного пользователя (текущий сеанс)
ACTIVE_USER=$(loginctl list-sessions --no-legend | awk '{print $3}' | head -n1)
USER_CONFIG="/home/$ACTIVE_USER/.config/power-mode-auto-changer/power-modes.conf"

if [ ! -f "$USER_CONFIG" ]; then
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

CURRENT_MODE="$(powerprofilesctl get 2>/dev/null)"

if [[ "${CURRENT_MODE}" == "${POWER_MODE}" ]]; then
    exit 0
fi

# #Define current lang
# source "$MAIN_SCRIPTS_DIR/common/define-current-lang.sh"

#connect translations 
source "$MAIN_SCRIPTS_DIR/common/lang/$NOTIFY_LANG.conf"



case "$POWER_MODE" in
    "power-saver")
        NOTIFY_TEXT=$CONFIGURATOR_TEXT_POWER_SAVER
        ;;
    "balanced")
        NOTIFY_TEXT=$CONFIGURATOR_TEXT_BALANCED
        ;;
    "performance")
        NOTIFY_TEXT=$CONFIGURATOR_TEXT_PERFORMANCE
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