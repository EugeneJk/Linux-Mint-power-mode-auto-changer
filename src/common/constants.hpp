#ifndef COMMON_CONSTANTS_HPP
#define COMMON_CONSTANTS_HPP

#include <string>

inline const std::string APP_NAME = "power-mode-auto-changer";
inline const std::string USER_SERVICE_NAME = APP_NAME + ".service";

/* Relative path from home folder to user configuration file */
inline const std::string USER_CONFIG_DIR =
    ".config/" + APP_NAME;
inline const std::string USER_CONFIG_REL =
    USER_CONFIG_DIR + "/power-modes.conf";

/* Absolute path to system config */
inline const std::string SYSTEM_CONFIG =
    "/etc/" + APP_NAME + "/config";

inline const std::string ON_AC_ICON = "ac-adapter-symbolic";
inline const std::string ON_BAT_ICON = "battery-symbolic";
inline const std::string ON_AC_ICON_OTHER = "ac-adapter";
inline const std::string ON_BAT_ICON_OTHER = "battery";

inline const char* LOCK_FILE = "/run/power-mode-auto-changer.lock";

#endif