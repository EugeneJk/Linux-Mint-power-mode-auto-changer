#include "parse-args.hpp"
#include <string>
#include <map>
#include <sstream>
#include <optional>

#include <iostream>

std::string detectLanguage(int argc, char *argv[])
{
    std::optional<std::string> forced;
    for (int i = 1; i < argc; ++i)
    {
        std::istringstream iss(argv[i]);
        std::string key, value;
        if (std::getline(iss, key, '=') && std::getline(iss, value))
        {
            if (key == "--lang")
            {
                forced = value;
            }
        }
    }

    if (forced)
    {
        if (*forced == "ru")
            return "ru_RU.UTF-8";
        if (*forced == "en")
            return "en_US.UTF-8";
    }

    const char *vars[] = {"LC_ALL", "LC_MESSAGES", "LANG"};
    std::string locale;

    for (auto v : vars)
    {
        const char *val = std::getenv(v);
        if (val && *val)
        {
            locale = val;
            break;
        }
    }

    if (locale.size() >= 2)
    {
        std::string code = locale.substr(0, 2);
        if (code == "ru")
            return "ru_RU.UTF-8";
        if (code == "en")
            return "en_US.UTF-8";
    }

    return "en_US.UTF-8";
}