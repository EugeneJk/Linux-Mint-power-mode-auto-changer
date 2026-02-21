show_notification() {
    local ACTIVE_UID DBUS_SESSION_BUS_ADDRESS
    ACTIVE_UID=$(id -u "$1")

    DBUS_SESSION_BUS_ADDRESS="unix:path=/run/user/$ACTIVE_UID/bus"

    sudo -u "$1" \
    DBUS_SESSION_BUS_ADDRESS=$DBUS_SESSION_BUS_ADDRESS \
    gdbus call --session \
    --dest org.Cinnamon \
    --object-path /org/Cinnamon \
    --method org.Cinnamon.ShowOSD \
    "{'icon': <'$2'>, 'label': <'$3'>}"
}
