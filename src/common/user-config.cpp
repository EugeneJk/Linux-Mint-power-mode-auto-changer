#include "user-config.hpp"
#include <string>
#include <map>
#include <optional>
#include "../utils/str-empty-checker.hpp"

/* Get power profile opition*/
std::optional<PowerProfile> parsePowerProfile(const std::string &value)
{
    if (value == "power-saver")
        return PowerProfile::PowerSaver;
    if (value == "balanced")
        return PowerProfile::Balanced;
    if (value == "performance")
        return PowerProfile::Performance;
    return std::nullopt;
}

UserConfig parceUserConfig(const std::map<std::string, std::string> &config)
{
    UserConfig result;
    result.onAc = parsePowerProfile(config.at("ON_AC")).value();
    result.onBat = parsePowerProfile(config.at("ON_BATTERY")).value();
    result.onAcText = strEmptyChecker(config.at("ON_AC_TEXT")).value();
    result.onBatText = strEmptyChecker(config.at("ON_BATTERY_TEXT")).value();

    return result;
}

std::string powerProfileToString(PowerProfile profile)
{
    switch (profile)
    {
    case PowerProfile::PowerSaver:
        return "power-saver";
    case PowerProfile::Balanced:
        return "balanced";
    case PowerProfile::Performance:
        return "performance";
    }
    return {}; // теоретически недостижимо
}