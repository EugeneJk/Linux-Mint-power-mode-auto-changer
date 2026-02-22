#ifndef COMMON_CONSTANTS_HPP
#define COMMON_CONSTANTS_HPP

#include <string>

inline const std::string APP_NAME = "power-mode-auto-changer";

/* Relative path from home folder to user configuration file */
inline const std::string USER_CONFIG_REL =
    ".config/" + APP_NAME + "/power-modes.conf";

/* Absolute path to system config */
inline const std::string SYSTEM_CONFIG =
    "/etc/" + APP_NAME + "/config";

inline const std::string ON_AC_ICON = "ac-adapter-symbolic";
inline const std::string ON_BAT_ICON = "battery-symbolic";

#endif