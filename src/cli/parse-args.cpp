#include "parse-args.hpp"
#include <string>
#include <map>
#include <sstream>
#include <optional>

#include <libintl.h>
#define _(String) gettext(String)

AppAction extractAciont(std::string value){
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


/* Check uset text for empty */
AppAction extractAction(int argc, char* argv[])
{
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
            currentAction = extractAciont(argv[i]);
        } else {
            throw std::runtime_error(_("Only one action supported"));
        }

    }
    if(!currentAction) return AppAction::Help;

    return currentAction.value();
}

