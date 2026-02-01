#!/bin/bash

set -e

CONFIG=/etc/power-change.conf
SCRIPT=/usr/local/bin/power-change.sh
RULE=/etc/udev/rules.d/99-power-change.rules

echo "Removing power-change configuration..."

if [ -f "$CONFIG" ]; then
    sudo rm "$CONFIG"
    echo "Removed $CONFIG"
else
    echo "$CONFIG not found"
fi

if [ -f "$SCRIPT" ]; then
    sudo rm "$SCRIPT"
    echo "Removed $SCRIPT"
else
    echo "$SCRIPT not found"
fi

if [ -f "$RULE" ]; then
    sudo rm "$RULE"
    echo "Removed $RULE"
else
    echo "$RULE not found"
fi

echo "Reloading udev rules..."
sudo udevadm control --reload

echo "Uninstallation completed."
