#include "help.hpp"
#include <iostream>

#include <libintl.h>
#define _(String) gettext(String)

void showHelp(){
    std::cout << _("Power Mode Auto Changer") << "\n";
    std::cout << _("Usage") << ":\n";
    std::cout << "\tpower-mode-auto-changer [ACTION] [OPTION]\n\n";
    
    std::cout << _("Actions") <<"\n";
    std::cout << "\t--status\t" <<_("Show current service and power mode status.") <<"\n";
    std::cout << "\t--configure\t" <<_("Run interactive configuration.") <<"\n";
    std::cout << "\t--help\t\t" <<_("Show this help message (default).") <<"\n";
    std::cout << "\t--version\t" <<_("Show program version.") <<"\n\n";
    
    std::cout << _("Options") <<"\n";
    std::cout << "\t--lang=ru\t" <<_("Force Russian language.") <<"\n";
    std::cout << "\t--lang=en\t" <<_("Force English language.") <<"\n\n";

    std::cout << _("Examples") <<"\n";
    std::cout << "\tpower-mode-auto-changer\n";
    std::cout << "\tpower-mode-auto-changer --status\n";
    std::cout << "\tpower-mode-auto-changer --configure\n";
    std::cout << "\tpower-mode-auto-changer --help\n";
    std::cout << "\tpower-mode-auto-changer --version\n";
    std::cout << "\tpower-mode-auto-changer --status --lang=ru\n\n";

    std::cout << _("Notes") <<"\n";
    std::cout << "• " << _("Only one action may be specified.") <<"\n";
    std::cout << "• " << _("If no action is specified, --help is used by default.") <<"\n";
    std::cout << "• " << _("Configuration is interactive.") <<"\n";
}
