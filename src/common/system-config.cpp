#include "system-config.hpp"
#include <string>
#include <map>
#include <optional>
#include "../utils/str-empty-checker.hpp"

SystemConfig parceSystemConfig(const std::map<std::string, std::string> &config)
{
    SystemConfig result;
    result.acStatusContainer = strEmptyChecker(config.at("AC_PATH")).value();

    return result;
}
