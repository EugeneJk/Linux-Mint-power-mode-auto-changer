#include <iostream>
#include "common/user.hpp"
#include "common/command.hpp"
#include "common/config-loader.hpp"
#include "common/constants.hpp"
#include "common/user-config.hpp"
#include "common/system-config.hpp"
#include "service/is-power-plugged.hpp"
#include "service/show-notification.hpp"
#include <string>
#include <map>

int main()
{
    try
    {
        // get current user info
        UserInfo user = getUser();
        
        // load user config
        std::string userConfigPath = "/home/" + user.name + "/" + USER_CONFIG_REL;
        UserConfig userConfig = parceUserConfig(loadConfig(userConfigPath));

        // load system config
        SystemConfig systemConfig = parceSystemConfig(loadConfig(SYSTEM_CONFIG));

        std::string cinnamonSessionPid = execCommand("pgrep -u " + user.name + " -f cinnamon-session-binary");
        bool isCinnamon = cinnamonSessionPid != "";

        bool isAcOn = isPowerPlugged(systemConfig.acStatusContainer);

        // define profile, icon and message to set and display
        std::string displayText;
        std::string newPowerProfile;
        std::string icon;
        if(isAcOn) {
            displayText = userConfig.onAcText;
            newPowerProfile = powerProfileToString(userConfig.onAc);
            icon = isCinnamon ? ON_AC_ICON : ON_AC_ICON_OTHER;
        } else {
            displayText = userConfig.onBatText;
            newPowerProfile = powerProfileToString(userConfig.onBat);
            icon = isCinnamon ? ON_BAT_ICON : ON_BAT_ICON_OTHER;
        }

        // Get current profile
        std::string currentPowerProfile = execCommand("powerprofilesctl get");

        // if new profile is the same as current then do nothing and finish
        if(currentPowerProfile == newPowerProfile) return 0;

        // set new profile
        execCommand("powerprofilesctl set " + newPowerProfile);
        
        // show notification
        showNotification(user, icon, displayText , isCinnamon);
    }
    catch (const std::exception &ex)
    {
        std::cerr << "Error: " << ex.what() << "\n";
        // silent exit with error
        return 1;
    }
    return 0;
}