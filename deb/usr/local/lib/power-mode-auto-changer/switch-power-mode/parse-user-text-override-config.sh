parse_user_text_override_config() {
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
            CUSTOM_TEXT_POWER_SAVER) CUSTOM_TEXT_POWER_SAVER="$value" ;;
            CUSTOM_TEXT_BALANCED) CUSTOM_TEXT_BALANCED="$value" ;;
            CUSTOM_TEXT_PERFORMANCE) CUSTOM_TEXT_PERFORMANCE="$value" ;;
        esac
    done < "$1"
}
