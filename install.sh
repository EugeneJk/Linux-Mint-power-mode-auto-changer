#!/bin/bash
echo
echo "========================================"
echo "         Power mode configuration       "
echo "       Конфигурация режимов питания     "
echo "========================================"
echo

AC_PS="\033[0;33m"      # оранжевый
AC_BAL="\033[0;32m"     # зелёный
AC_PERF="\033[1;32m"    # ярко-зелёный

BAT_PS="\033[0;32m"     # зелёный
BAT_BAL="\033[0;33m"    # жёлтый
BAT_PERF="\033[0;31m"   # красный

GREEN_BRIGHT="\033[1;32m"
GREEN="\033[0;32m"
RESET="\033[0m"

# Find path to check AC status
AC_PATH=$(for d in /sys/class/power_supply/*; do
    if [ "$(cat "$d/type" 2>/dev/null)" = "Mains" ]; then
        echo "$d"
        break
    fi
done)

# If empty, stop installation
if [ -z "$AC_PATH" ]; then
    echo "Can't find AC device. Installation stopped."
    echo "Не возможно найти устройство притания от сети. Установка остановлена."
    exit 1
fi

echo -e "Please select the power mode when running on ${GREEN_BRIGHT}AC power${RESET}:"
echo -e "Пожалуйста, выберите режим питания при ${GREEN_BRIGHT}подключенном блоке питания${RESET}:"
echo -e "1) ${AC_PS}Power saver - Энергосбережение${RESET}"
echo -e "2) ${AC_BAL}Balanced - Сбалансированный${RESET}"
echo -e "3) ${AC_PERF}Performance - Производительность${RESET}"
echo "Any other input - abort installation"
echo "Любой другой ввод прервет установку"

echo

read -rp "[1-3]: " choice

case "$choice" in
    1)
        ON_AC="power-saver"
        ;;
    2)
        ON_AC="balanced"
        ;;
    3)
        ON_AC="performance"
        ;;
    *)
        echo "Установка прервана."
        exit 1
        ;;
esac

echo
echo -e "Please select the power mode when running on ${GREEN}battery power${RESET}:"
echo -e "1) ${BAT_PS}Power saver - Энергосбережение${RESET}"
echo -e "2) ${BAT_BAL}Balanced - Сбалансированный${RESET}"
echo -e "3) ${BAT_PERF}Performance - Производительность${RESET}"
echo "Any other input - abort installation"
echo "Любой другой ввод прервет установку"

echo

read -rp "[1-3]: " choice

case "$choice" in
    1)
        ON_BATTERY="power-saver"
        ;;
    2)
        ON_BATTERY="balanced"
        ;;
    3)
        ON_BATTERY="performance"
        ;;
    *)
        echo "Установка прервана."
        exit 1
        ;;
esac

CONFIG=/etc/power-mode-auto-changer.conf

echo
echo "Saving configuration to $CONFIG..."
echo "Сохранение настроек в $CONFIG..."

sudo tee "$CONFIG" > /dev/null <<EOF
# Power change configuration
# Generated on $(date)

AC_PATH=${AC_PATH}/online
ON_AC=${ON_AC}
ON_BATTERY=${ON_BATTERY}
EOF

sudo chown root:root "$CONFIG"
sudo chmod 644 "$CONFIG"

echo "Copying main script..."
echo "Копируем основной скрипт..."
sudo cp power-mode-auto-changer.sh /usr/local/bin/power-mode-auto-changer.sh
sudo chown root:root /usr/local/bin/power-mode-auto-changer.sh
sudo chmod 755 /usr/local/bin/power-mode-auto-changer.sh

echo "Copying udev rule..."
echo "Копируем правило udev..."
sudo cp power-mode-auto-changer.rules /etc/udev/rules.d/99-power-mode-auto-changer.rules
sudo chown root:root /etc/udev/rules.d/99-power-mode-auto-changer.rules
sudo chmod 644 /etc/udev/rules.d/99-power-mode-auto-changer.rules

echo "Reloading udev rules..."
echo "Перезагружаем правила udev..."
sudo udevadm control --reload

echo
echo "========================================"
echo "         Installation completed         "
echo "           Установка завершена          "
echo "========================================"
echo
