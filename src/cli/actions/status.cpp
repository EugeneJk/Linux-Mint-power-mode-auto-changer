#include "status.hpp"
#include "../../common/command.hpp"
#include "../../common/constants.hpp"
#include <string>
#include <iostream>

#include <libintl.h>
#define _(String) gettext(String)

void showStatus(){
    std::cout << "Status" << "\n";
}
