validate_user_config_file() {
    local active_user="$1"
    local file="$2"
    local max_size=8192   # 8 KB достаточно для текстовых override

    # 1. существует
    [ -e "$file" ] || return 1

    # 2. обычный файл
    [ -f "$file" ] || return 1

    # 3. не симлинк
    [ ! -L "$file" ] || return 1

    # 4. владелец — активный пользователь
    [ "$(stat -c %U "$file")" = "$active_user" ] || return 1

    # 5. размер ограничен
    [ "$(stat -c %s "$file")" -le "$max_size" ] || return 1

    # 6. запрет записи для others
    local perm
    perm=$(stat -c %a "$file")
    local others
    # последняя цифра — права others
    others=$((perm % 10))

    # если установлен бит записи
    if (( others & 2 )); then
        return 1
    fi

    return 0
}
