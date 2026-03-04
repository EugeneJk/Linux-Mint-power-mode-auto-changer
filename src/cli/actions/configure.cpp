#include "configure.hpp"
#include "../../common/command.hpp"
#include "../../common/constants.hpp"
#include <string>
#include <iostream>
#include "../../common/system-config.hpp"
#include "../../common/config-loader.hpp"
#include "../../common/colors.hpp"
#include "../../common/constants.hpp"
#include "../../common/user-config.hpp"
#include "../../common/user.hpp"
#include <filesystem>

#include <libintl.h>
#define _(String) gettext(String)

void runConfiguration()
{
    try
    {
        // get current user info
        UserInfo user = getUser();

        std::cout << "\n"
                  << _("Power Mode Auto Changer") << "\n";
        std::cout << _("Interactive configuration mode") << "\n\n";

        SystemConfig systemConfig = parceSystemConfig(loadConfig(SYSTEM_CONFIG));

        UserConfig userConfig;
        std::string input;
        std::string selectedProfileName;

        std::cout << _("Select the power mode when running") << " " << color::bright_cyan << _("on AC power") << color::reset << "\n\n";
        std::cout << "    1 - " << color::bright_yellow << powerProfileToNameString(PowerProfile::PowerSaver) << color::reset << "\n";
        std::cout << "    2 - " << color::green << powerProfileToNameString(PowerProfile::Balanced) << color::reset << "\n";
        if (systemConfig.isPerformanceAvailable){
            std::cout << "    3 - " << color::bright_green << powerProfileToNameString(PowerProfile::Performance) << color::reset << "\n";
        }
        std::cout << "    q - " << _("Quit") << "\n\n";

        while (true)
        {
            std::cout << _("Enter choice") << (systemConfig.isPerformanceAvailable ? " [1-3, q]: " : " [1, 2, q]: ");
            std::getline(std::cin, input);

            if (input == "q" || input == "Q")
            {
                exit(0);
            }

            if (input == "1" || input == "2" || (input == "3" && systemConfig.isPerformanceAvailable))
            {
                userConfig.onAc = input == "1" ? PowerProfile::PowerSaver : input == "2" ? PowerProfile::Balanced
                                                                                         : PowerProfile::Performance;
                break;
            }
        }

        selectedProfileName = powerProfileToNameString(userConfig.onAc);
        std::cout << "\n";
        std::cout << _("Mode selected") << ": " << color::bright_cyan << selectedProfileName << color::reset << "\n\n";
        std::cout << _("Enter notification text shown when this mode is activated") << "\n";
        std::cout << _("Press Enter to use the default value.") << "\n\n";
        std::cout << _("Notification text") << " [" << selectedProfileName << "]: ";
        std::getline(std::cin, input);
        userConfig.onAcText = input == "" ? selectedProfileName : input;

        std::cout << "\n";
        std::cout << _("Select the power mode when running") << " " << color::bright_cyan << _("on battery power") << color::reset << "\n\n";
        std::cout << "    1 - " << color::green << powerProfileToNameString(PowerProfile::PowerSaver) << color::reset << "\n";
        std::cout << "    2 - " << color::yellow << powerProfileToNameString(PowerProfile::Balanced) << color::reset << "\n";
        if (systemConfig.isPerformanceAvailable){
            std::cout << "    3 - " << color::red << powerProfileToNameString(PowerProfile::Performance) << color::reset << "\n";
        }
        std::cout << "    q - " << _("Quit") << "\n\n";

        while (true)
        {
            std::cout << _("Enter choice") << (systemConfig.isPerformanceAvailable ? " [1-3, q]: " : " [1, 2, q]: ");
            std::getline(std::cin, input);

            if (input == "q" || input == "Q")
            {
                exit(0);
            }

            if (input == "1" || input == "2" || (input == "3" && systemConfig.isPerformanceAvailable))
            {
                userConfig.onBat = input == "1" ? PowerProfile::PowerSaver : input == "2" ? PowerProfile::Balanced
                                                                                          : PowerProfile::Performance;
                break;
            }
        }

        selectedProfileName = powerProfileToNameString(userConfig.onBat);
        std::cout << "\n";
        std::cout << _("Mode selected") << ": " << color::bright_cyan << selectedProfileName << color::reset << "\n\n";
        std::cout << _("Enter notification text shown when this mode is activated") << "\n";
        std::cout << _("Press Enter to use the default value.") << "\n\n";
        std::cout << _("Notification text") << " [" << selectedProfileName << "]: ";
        std::getline(std::cin, input);
        userConfig.onBatText = input == "" ? selectedProfileName : input;

        std::cout << "\n";
        std::cout << _("Enable power mode synchronization at system startup?") << "\n\n";

        std::string syncMode = "disable";
        while (true)
        {
            std::cout << "[y] " << _("Yes") << " [n] " << _("No") << " [q] " << _("Quit") << ": ";
            std::getline(std::cin, input);

            if (input == "q" || input == "Q")
            {
                exit(0);
            }

            if (input == "y" || input == "Y")
            {
                syncMode = "enable";
                break;
            }
            if (input == "n" || input == "N")
            {
                break;
            }
        }

        std::string userConfigPath = "/home/" + user.name + "/" + USER_CONFIG_REL;
        std::string dir = "/home/" + user.name + "/" + USER_CONFIG_DIR;

        if (!std::filesystem::exists(dir))
        {
            if (!std::filesystem::create_directories(dir))
            {
                std::cout << color::critical_error << _("Can't create config folder") << " " << dir << color::reset << "\n";
                exit(1);
            }
        }

        if (!saveUserConfig(userConfigPath, userConfig))
        {
            std::cout << color::critical_error << _("Can't save user configuration file") << " " << userConfigPath << color::reset << "\n";
            exit(1);
        }

        std::string command = "systemctl --user " + syncMode + " --now " + USER_SERVICE_NAME;
        execCommand(command);

        std::cout << "\n"
                  << _("Configuration saved successfully.") << "\n";
    }
    catch (const std::exception &e)
    {
        std::cout << color::critical_error << _("AC power source not detected. Unable to determine power state. Exiting.") << color::reset << "\n";
        exit(1);
    }
}
