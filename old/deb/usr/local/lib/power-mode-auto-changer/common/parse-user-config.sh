parse_user_config() {
    local key value

    while IFS='=' read -r key value; do
        # убрать пробелы по краям
        key="${key#"${key%%[![:space:]]*}"}"
        key="${key%"${key##*[![:space:]]}"}"

        value="${value#"${value%%[![:space:]]*}"}"
        value="${value%"${value##*[![:space:]]}"}"

        # пропуск пустых строк и комментариев
        [[ -z "$key" || "$key" == \#* ]] && continue

        case "$key" in
            ON_AC) ON_AC="$value" ;;
            ON_BATTERY) ON_BATTERY="$value" ;;
            NOTIFY_LANG) NOTIFY_LANG="$value" ;;
        esac
    done < "$1"
}
