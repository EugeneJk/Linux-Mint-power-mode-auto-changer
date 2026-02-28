#include "user-config.hpp"
#include <string>
#include <map>
#include <optional>
#include "../utils/str-empty-checker.hpp"
#include <fstream>
#include <iostream>

#include <libintl.h>
#define _(String) gettext(String)
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

std::string powerProfileToNameString(PowerProfile profile)
{
    switch (profile)
    {
    case PowerProfile::PowerSaver:
        return _("Power saver");
    case PowerProfile::Balanced:
        return _("Balanced");
    case PowerProfile::Performance:
        return _("Performance");
    }
    return {}; // теоретически недостижимо
}

bool saveUserConfig(const std::string &path, UserConfig config)
{
    std::ofstream file(path, std::ios::trunc);
    if (!file.is_open())
        return false;

    file << "ON_AC=" << powerProfileToString(config.onAc) << "\n";
    file << "ON_BATTERY=" << powerProfileToString(config.onBat) << "\n";
    file << "ON_AC_TEXT=" << config.onAcText << "\n";
    file << "ON_BATTERY_TEXT=" << config.onBatText << "\n";

    if (!file.good())
        return false;

    file.close();
    return true;
}