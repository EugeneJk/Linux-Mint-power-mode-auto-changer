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
#include <iostream>
#include <fcntl.h>
#include <sys/file.h>
#include <unistd.h>
#include <cstring>
#include <cerrno>
int main()
{
    // Create blocking to avoid run the same simultaniously
    int fd = open(LOCK_FILE, O_CREAT | O_RDWR, 0644);
    if (fd == -1)
    {
        std::cerr << "open() failed: "
                  << std::strerror(errno) << std::endl;
        return 1;
    }

    // wait for lock release if execution in the enother process
    if (flock(fd, LOCK_EX) == -1)
    {
        std::cerr << "flock() failed: "
                  << std::strerror(errno) << std::endl;
        close(fd);
        return 1;
    }

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
        if (isAcOn)
        {
            displayText = userConfig.onAcText;
            newPowerProfile = powerProfileToString(userConfig.onAc);
            icon = isCinnamon ? ON_AC_ICON : ON_AC_ICON_OTHER;
        }
        else
        {
            displayText = userConfig.onBatText;
            newPowerProfile = powerProfileToString(userConfig.onBat);
            icon = isCinnamon ? ON_BAT_ICON : ON_BAT_ICON_OTHER;
        }

        // Get current profile
        std::string currentPowerProfile = execCommand("powerprofilesctl get");

        // if new profile is the same as current then do nothing and finish
        if (currentPowerProfile == newPowerProfile)
        {
            // release lock
            flock(fd, LOCK_UN);
            close(fd);
            return 0;
        }

        // set new profile
        execCommand("powerprofilesctl set " + newPowerProfile);

        // show notification
        showNotification(user, icon, displayText, isCinnamon);
    }
    catch (const std::exception &ex)
    {
        std::cerr << "Error: " << ex.what() << "\n";
        // silent exit with error
        // release lock
        flock(fd, LOCK_UN);
        close(fd);
        return 1;
    }
    // release lock
    flock(fd, LOCK_UN);
    close(fd);
    return 0;
}