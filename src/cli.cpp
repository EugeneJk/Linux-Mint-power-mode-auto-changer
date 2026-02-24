// power_mode_auto_changer_v2.cpp

#include <iostream>
#include "common/constants.hpp"
#include "cli/parse-args.hpp"
#include "cli/detect-lang.hpp"
#include "cli/actions/version.hpp"
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
            std::cout << "Show help";
            break;
        case AppAction::Status:
            std::cout << "Show status";
            break;

        case AppAction::Version:
            showVersion();
            break;

        case AppAction::InteractiveConfig:
            std::cout << "Run interactive configuration";
            break;
        }
    }
    catch (const std::exception &e)
    {
        std::cerr << e.what() << '\n';
    }

    return 0;
}