#ifndef COMMON_USER_CONFIG_HPP
#define COMMON_USER_CONFIG_HPP

#include <string>
#include <map>
#include <optional>

/* Power Profile types */
enum class PowerProfile
{
    PowerSaver,
    Balanced,
    Performance
};

/* User configuration struct */
struct UserConfig
{
    PowerProfile onAc;
    PowerProfile onBat;
    std::string onAcText;
    std::string onBatText;
};

/* Parses user configuration */
UserConfig parceUserConfig(const std::map<std::string, std::string> &config);

/* Prints power profile option */
std::string powerProfileToString(PowerProfile profile);

std::string powerProfileToNameString(PowerProfile profile);

#endif