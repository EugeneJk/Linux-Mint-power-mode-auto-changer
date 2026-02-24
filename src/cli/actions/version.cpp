#include "version.hpp"
#include "../../common/command.hpp"
#include "../../common/constants.hpp"
#include <string>
#include <iostream>

#include <libintl.h>
#define _(String) gettext(String)

void showVersion(){
    std::string command = "dpkg-query -W -f='${Version}' \"" + APP_NAME + "\"";
    std::string version = execCommand(command);
    std::cout << _("Version") << ": " << version << "\n";
}
