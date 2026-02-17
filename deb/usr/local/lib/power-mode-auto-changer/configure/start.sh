echo
echo "========================================"
echo "      $CONFIGURATOR_TEXT_HEADER"
echo "========================================"
echo

MAIN_CONFIG=/etc/power-mode-auto-changer/config
CONFIG_DIR=~/.config/power-mode-auto-changer
CONFIG_FILE_POWER_MODES=power-modes.conf
USER_SERVICE="power-mode-auto-changer.service"

source "$MAIN_CONFIG"

# If empty, stop installation
if [ -z "$AC_PATH" ]; then
    echo "$CONFIGURATOR_TEXT_NO_AC"
    exit 1
fi


AC_PS="\033[0;33m"      # оранжевый
AC_BAL="\033[0;32m"     # зелёный
AC_PERF="\033[1;32m"    # ярко-зелёный

BAT_PS="\033[0;32m"     # зелёный
BAT_BAL="\033[0;33m"    # жёлтый
BAT_PERF="\033[0;31m"   # красный

GREEN_BRIGHT="\033[1;32m"
GREEN="\033[0;32m"
RESET="\033[0m"

echo -e "$CONFIGURATOR_TEXT_SELECT_POWER_MODE_ON ${GREEN_BRIGHT}$CONFIGURATOR_TEXT_AC_POWER${RESET}:"
echo -e "1 - ${AC_PS}$CONFIGURATOR_TEXT_POWER_SAVER${RESET}"
echo -e "2 - ${AC_BAL}$CONFIGURATOR_TEXT_BALANCED${RESET}"
echo -e "3 - ${AC_PERF}$CONFIGURATOR_TEXT_PERFORMANCE${RESET}"
echo -e "q - $CONFIGURATOR_TEXT_EXIT"

echo

while true; do
    read -rp "[1-3 or q]: " choice

    case "$choice" in
        1)
            ON_AC="power-saver"
            break
            ;;
        2)
            ON_AC="balanced"
            break
            ;;
        3)
            ON_AC="performance"
            break
            ;;
        q|Q)
            exit 1
            ;;
        *)
            echo "$CONFIGURATOR_TEXT_INVALID_INPUT"
            ;;
    esac
done

echo
echo -e "$CONFIGURATOR_TEXT_SELECT_POWER_MODE_ON ${GREEN}$CONFIGURATOR_TEXT_BATTERY_POWER${RESET}:"
echo -e "1) ${BAT_PS}$CONFIGURATOR_TEXT_POWER_SAVER${RESET}"
echo -e "2) ${BAT_BAL}$CONFIGURATOR_TEXT_BALANCED${RESET}"
echo -e "3) ${BAT_PERF}$CONFIGURATOR_TEXT_PERFORMANCE${RESET}"
echo -e "q - $CONFIGURATOR_TEXT_EXIT"

echo

while true; do
    read -rp "[1-3 or q]: " choice

    case "$choice" in
        1)
            ON_BATTERY="power-saver"
            break
            ;;
        2)
            ON_BATTERY="balanced"
            break
            ;;
        3)
            ON_BATTERY="performance"
            break
            ;;
        q|Q)
            exit 1
            ;;
        *)
            echo "$CONFIGURATOR_TEXT_INVALID_INPUT"
            ;;
    esac
done

echo
echo -e "$CONFIGURATOR_TEXT_SELECT_AUTO_SYNC ${GREEN}$CONFIGURATOR_TEXT_SELECT_AUTO_SYNC_ON${RESET}:"
echo -e "1) ${GREEN_BRIGHT}$CONFIGURATOR_TEXT_AUTO_SYNC_ENABLED${RESET}"
echo -e "2) ${GREEN}$CONFIGURATOR_TEXT_AUTO_SYNC_DISABLED${RESET}"
echo -e "q - $CONFIGURATOR_TEXT_EXIT"

while true; do
    read -rp "[1-3 or q]: " choice

    case "$choice" in
        1)
            systemctl --user enable --now "$USER_SERVICE"
            break
            ;;
        2)
            systemctl --user disable --now "$USER_SERVICE"
            break
            ;;
        q|Q)
            exit 1
            ;;
        *)
            echo "$CONFIGURATOR_TEXT_INVALID_INPUT"
            ;;
    esac
done


mkdir -p $CONFIG_DIR
CONFIG="$CONFIG_DIR/$CONFIG_FILE_POWER_MODES"

tee "$CONFIG" > /dev/null <<EOF
# Power mode change configuration
# Generated on $(date)

ON_AC=${ON_AC}
ON_BATTERY=${ON_BATTERY}
EOF

echo
echo -e "$CONFIGURATOR_TEXT_SAVED_TO $CONFIG"
