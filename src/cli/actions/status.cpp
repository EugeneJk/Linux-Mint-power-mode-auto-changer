#include "status.hpp"
#include "../../common/colors.hpp"
#include "../../common/constants.hpp"
#include "../../common/command.hpp"
#include "../../common/user.hpp"
#include "../../common/user-config.hpp"
#include "../../common/system-config.hpp"
#include "../../common/config-loader.hpp"
#include <string>
#include <iostream>

#include <libintl.h>
#define _(String) gettext(String)

void showStatus()
{
    // get current user info
    UserInfo user = getUser();

    try
    {
        SystemConfig systemConfig = parceSystemConfig(loadConfig(SYSTEM_CONFIG));
    }
    catch (const std::exception &e)
    {
        std::cout << color::critical_error << _("AC power source not detected. Unable to determine power state. Exiting.") << color::reset << "\n";
        exit(1);
    }

    try
    {
        // load user config
        std::string userConfigPath = "/home/" + user.name + "/" + USER_CONFIG_REL;
        UserConfig userConfig = parceUserConfig(loadConfig(userConfigPath));

        // check if startup sync service is on
        // systemctl --user is-enabled --quiet $USER_SERVICE
        std::string command = "systemctl --user is-enabled " + USER_SERVICE_NAME;
        bool isSyncServiceEnabled = "enabled" == execCommand(command);

        std::string syncStatusText = isSyncServiceEnabled ? _("Enabled") : _("Disabled");
        std::string syncColor = (isSyncServiceEnabled ? color::green : color::bright_yellow);
        std::cout << _("Power mode synchronization on startup") << ": " << syncColor << syncStatusText << color::reset << "\n";

        std::string acPowerModeColor = color::bright_yellow;
        if (userConfig.onAc == PowerProfile::Performance)
            acPowerModeColor = color::bright_green;
        else if (userConfig.onAc == PowerProfile::Balanced)
            acPowerModeColor = color::green;

        std::cout << _("Power mode when connected to AC") << ": "
                  << acPowerModeColor
                  << powerProfileToNameString(userConfig.onAc)
                  << color::reset << "\n";
        std::cout << "\t" << _("Notification text") << ": "
                  << acPowerModeColor
                  << userConfig.onAcText
                  << color::reset << "\n";

        std::string batPowerModeColor = color::red;
        if (userConfig.onBat == PowerProfile::Balanced)
            batPowerModeColor = color::bright_yellow;
        else if (userConfig.onBat == PowerProfile::PowerSaver)
            batPowerModeColor = color::green;

        std::cout << _("Power mode when running on battery") << ": "
                  << batPowerModeColor
                  << powerProfileToNameString(userConfig.onBat)
                  << color::reset << "\n";
        std::cout << "\t" << _("Notification text") << ": "
                  << batPowerModeColor
                  << userConfig.onBatText
                  << color::reset << "\n";
    }
    catch (const std::exception &e)
    {
        std::cout << color::bright_yellow << _("Application is not configured. Run the configurator to set it up. Exiting.") << "\n"
                  << color::reset;
        exit(1);
    }
}

/*
echo -e "$STATUS_TEXT_SYNC: ${START_UP_AUTO_SYNC_COLOR}$START_UP_AUTO_SYNC_STATUS${RESET}"
echo -e "$STATUS_TEXT_ON_AC: ${ON_AC_COLOR}$NOTIFY_TEXT_ON_AC${RESET}"
echo -e "$STATUS_TEXT_ON_BAT: ${ON_BAT_COLOR}$NOTIFY_TEXT_ON_BAT${RESET}"
*/