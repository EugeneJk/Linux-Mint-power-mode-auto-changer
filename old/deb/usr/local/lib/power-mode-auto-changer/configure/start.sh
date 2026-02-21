echo
echo "========================================"
echo "      $CONFIGURATOR_TEXT_HEADER"
echo "========================================"
echo

source "$MAIN_CONFIG"

# If empty, stop installation
if [ -z "$AC_PATH" ]; then
    echo "$CONFIGURATOR_TEXT_NO_AC"
    exit 1
fi


echo -e "$CONFIGURATOR_TEXT_SELECT_POWER_MODE_ON ${GREEN_BRIGHT}$CONFIGURATOR_TEXT_AC_POWER${RESET}:"
echo -e "1) ${ORANGE}$CONFIGURATOR_TEXT_POWER_SAVER${RESET}"
echo -e "2) ${GREEN}$CONFIGURATOR_TEXT_BALANCED${RESET}"
echo -e "3) ${GREEN_BRIGHT}$CONFIGURATOR_TEXT_PERFORMANCE${RESET}"
echo -e "q) $CONFIGURATOR_TEXT_EXIT"

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
echo -e "1) ${GREEN}$CONFIGURATOR_TEXT_POWER_SAVER${RESET}"
echo -e "2) ${ORANGE}$CONFIGURATOR_TEXT_BALANCED${RESET}"
echo -e "3) ${RED}$CONFIGURATOR_TEXT_PERFORMANCE${RESET}"
echo -e "q) $CONFIGURATOR_TEXT_EXIT"

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
echo -e "1) ${GREEN}$CONFIGURATOR_TEXT_AUTO_SYNC_ENABLED${RESET}"
echo -e "2) ${ORANGE}$CONFIGURATOR_TEXT_AUTO_SYNC_DISABLED${RESET}"
echo -e "q) $CONFIGURATOR_TEXT_EXIT"

while true; do
    read -rp "[1-3 or q]: " choice

    case "$choice" in
        1)
            SYNC_MODE="enable"
            break
            ;;
        2)
            SYNC_MODE="disable"
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


mkdir -p $USER_CONFIG_DIR
CONFIG="$USER_CONFIG_DIR/$USER_CONFIG_FILE"

tee "$CONFIG" > /dev/null <<EOF
# Power mode change configuration
# Generated on $(date)

ON_AC=${ON_AC}
ON_BATTERY=${ON_BATTERY}
NOTIFY_LANG=${LANG_SELECTED}
EOF

echo
echo -e "$CONFIGURATOR_TEXT_SAVED_TO $CONFIG"

systemctl --user $SYNC_MODE --now "$USER_SERVICE"
