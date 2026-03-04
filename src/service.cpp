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
#include <syslog.h>

int main()
{
    openlog(APP_NAME.c_str(), LOG_PID, LOG_DAEMON);
    syslog(LOG_INFO, "Started ...");
    // Create blocking to avoid run the same simultaniously
    const char* runtimeDir = getenv("XDG_RUNTIME_DIR");
    std::string lockPath = std::string(runtimeDir) + LOCK_FILE;    
    int fd = open(lockPath.c_str(), O_CREAT | O_RDWR, 0644);
    if (fd == -1)
    {
        syslog(LOG_ERR, "open() failed: %s", std::strerror(errno));
        closelog();
        return 1;
    }

    // wait for lock release if execution in the enother process
    if (flock(fd, LOCK_EX) == -1)
    {
        syslog(LOG_ERR, "flock() failed: %s", std::strerror(errno));
        close(fd);
        closelog();
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
            syslog(LOG_INFO, "Power cable is plugged in");
            displayText = userConfig.onAcText;
            newPowerProfile = powerProfileToString(userConfig.onAc);
            icon = isCinnamon ? ON_AC_ICON : ON_AC_ICON_OTHER;
        }
        else
        {
            syslog(LOG_INFO, "Power cable is unplugged");
            displayText = userConfig.onBatText;
            newPowerProfile = powerProfileToString(userConfig.onBat);
            icon = isCinnamon ? ON_BAT_ICON : ON_BAT_ICON_OTHER;
        }

        // Get current profile
        std::string currentPowerProfile = execCommand("powerprofilesctl get");

        // if new profile is the same as current then do nothing and finish
        if (currentPowerProfile == newPowerProfile)
        {
            syslog(LOG_INFO, "Current profile is the same as required (%s) - no action needed.", currentPowerProfile.c_str());
            // release lock
            flock(fd, LOCK_UN);
            close(fd);
            closelog();
            return 0;
        }

        syslog(LOG_INFO, "Switching from  %s to %s", currentPowerProfile.c_str(), newPowerProfile.c_str());
        // set new profile
        execCommand("powerprofilesctl set " + newPowerProfile);

        std::string updatedPowerProfile = execCommand("powerprofilesctl get");
        syslog(LOG_INFO, "Profile after switch: %s", updatedPowerProfile.c_str());

        // show notification
        syslog(LOG_INFO, "Showing %s noticiation", isCinnamon ? "OSD" : "Default");
        showNotification(user, icon, displayText, isCinnamon);
        syslog(LOG_INFO, "Finished");
    }
    catch (const std::exception &ex)
    {
        syslog(LOG_ERR, "Error: %s" , ex.what());
        // silent exit with error
        // release lock
        flock(fd, LOCK_UN);
        close(fd);
        closelog();
        return 1;
    }
    // release lock
    flock(fd, LOCK_UN);
    close(fd);
    closelog();
    return 0;
}