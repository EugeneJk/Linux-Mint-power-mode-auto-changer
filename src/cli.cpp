// power_mode_auto_changer_v2.cpp

#include <iostream>
#include "common/constants.hpp"
#include "cli/parse-args.hpp"
#include "cli/detect-lang.hpp"
#include "cli/actions/version.hpp"
#include "cli/actions/help.hpp"
#include "cli/actions/status.hpp"
#include "cli/actions/configure.hpp"
#include <libintl.h>
#define _(String) gettext(String)

int main(int argc, char *argv[])
{
    std::string language = detectLanguage(argc, argv);

    unsetenv("LANGUAGE");
    setenv("LC_MESSAGES", language.c_str(), 1);
    setlocale(LC_ALL, "");
    bindtextdomain(APP_NAME.c_str(), "/usr/share/locale");
    textdomain(APP_NAME.c_str());

    try
    {
        AppAction action = extractAction(argc, argv);
        switch (action)
        {
        case AppAction::Help:
            showHelp();
            break;
        case AppAction::Status:
            showStatus();
            break;
        case AppAction::Version:
            showVersion();
            break;
        case AppAction::MenuInteractiveConfig:
        case AppAction::InteractiveConfig:
            runConfiguration();
            break;
        }
        if(action == AppAction::MenuInteractiveConfig){
            std::cout << "\n" << _("Press Enter to close this window...");
            std::string dummy;
            std::getline(std::cin, dummy);            
        }
    }
    catch (const std::exception &e)
    {
        std::cerr << e.what() << '\n';
    }

    return 0;
}