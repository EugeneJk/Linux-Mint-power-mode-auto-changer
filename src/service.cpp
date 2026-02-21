#include <iostream>
#include "common/user.hpp"
#include "common/command.hpp"
#include "common/config-loader.hpp"
#include "common/constants.hpp"
#include "common/user-config.hpp"
#include <string>
#include <map>

int main()
{
    std::cout << "Switch power mode service\n";

    try
    {
        // get current user info
        UserInfo user = getUser();
        std::cout << "User: " << user.name << " (uid=" << user.uid << ")\n\n";
        
        // load user config
        std::string userConfigPath = "/home/" + user.name + "/.config/power-mode-auto-changer/power-modes.conf";
        UserConfig userConfig = parceUserConfig(loadConfig(userConfigPath));

        std::cout << "On ac: " << powerProfileToString(userConfig.onAc) << "\n";
        std::cout << "On bat: " << powerProfileToString(userConfig.onBat) << "\n";
        std::cout << "On ac text: " << userConfig.onAcText << "\n";
        std::cout << "On bat text: " << userConfig.onBatText << "\n\n";

        std::cout << "Get current power profile\n";
        std::cout << "Check with new profile\n";
        std::cout << "Switch profile if needed\n";
        std::cout << "Show notification if needed\n";
    }
    catch (const std::exception &ex)
    {
        std::cerr << "Error: " << ex.what() << "\n";
        return 1;
    }
    return 0;
}