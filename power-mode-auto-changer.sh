#!/bin/bash
set -e

source /etc/power-mode-auto-changer.conf

STATE=$(cat "$AC_PATH")

if [ "$STATE" = "1" ]; then
    powerprofilesctl set "$ON_AC"
else
    powerprofilesctl set "$ON_BATTERY"
fi