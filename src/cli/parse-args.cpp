#include "parse-args.hpp"
#include <string>
#include <map>
#include <sstream>
#include <optional>
#include <string_view>
#include <iostream>

#include <libintl.h>
#define _(String) gettext(String)

AppAction convertStringToAction(std::string value){
    if (value == "--help")
        return AppAction::Help;
    if (value == "--status")
        return AppAction::Status;
    if (value == "--version")
        return AppAction::Version;
    if (value == "--configure")
        return AppAction::InteractiveConfig;
    throw std::runtime_error(_("Unknown action"));    
}

AppAction extractAction(int argc, char* argv[])
{
    bool isFromMenu = false;
    std::optional<AppAction> currentAction;

    for (int i = 1; i < argc; ++i)
    {
        std::istringstream iss(argv[i]);
        std::string key, value;
        if (std::getline(iss, key, '=') && std::getline(iss, value))
        {
            if(key != "--lang"){
                throw std::runtime_error(_("Unknown parameter"));
            }
        } else if(!currentAction){
            if (std::string_view(argv[i]) == "--from-menu") {
                isFromMenu = true;
                continue;
            }
            currentAction = convertStringToAction(argv[i]);
        } else {
            if (std::string_view(argv[i]) == "--from-menu") {
                isFromMenu = true;
                continue;
            }
            throw std::runtime_error(_("Only one action supported"));
        }

    }
    if(!currentAction) return AppAction::Help;

    if(currentAction.value() == AppAction::InteractiveConfig && isFromMenu)
        return AppAction::MenuInteractiveConfig;

    return currentAction.value();
}

