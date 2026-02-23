#include "parse-args.hpp"
#include <string>

#include <iostream>

/* Check uset text for empty */
AppParams parseArgs(int argc, char* argv[])
{
    // Печать аргументов
    std::cout << "Arguments (" << argc - 1 << "):\n";
    for (int i = 1; i < argc; ++i)
    {
        std::cout << "  argv[" << i << "] = " << argv[i] << "\n";
    }


    AppParams result;
    result.action = AppAction::Help;
    result.lang = "ru";
    return result;
}
