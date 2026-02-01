#!/bin/bash

set -e

CONFIG=/etc/power-change.conf
SCRIPT=/usr/local/bin/power-change.sh
RULE=/etc/udev/rules.d/99-power-change.rules

echo "Removing files..."
echo "Удаляем файлы..."

if [ -f "$CONFIG" ]; then
    sudo rm "$CONFIG"
    echo "Removed $CONFIG"
    echo "Удален $CONFIG"
else
    echo "$CONFIG not found"
    echo "$CONFIG не найден"
fi

if [ -f "$SCRIPT" ]; then
    sudo rm "$SCRIPT"
    echo "Removed $SCRIPT"
    echo "Удален $SCRIPT"
else
    echo "$SCRIPT not found"
    echo "$SCRIPT не найден"
fi

if [ -f "$RULE" ]; then
    sudo rm "$RULE"
    echo "Removed $RULE"
    echo "Удален $RULE"
else
    echo "$RULE not found"
    echo "$RULE не найден"
fi

echo "Reloading udev rules..."
echo "Перезагружаем правила udev..."

sudo udevadm control --reload

echo "Uninstallation completed."
echo "Удаление завершено."
