#include "version.hpp"
#include "../../common/command.hpp"
#include "../../common/constants.hpp"
#include <string>
#include <iostream>

#include <libintl.h>
#define _(String) gettext(String)

void showHelp(){
    std::cout << "Status" << "\n";
}
