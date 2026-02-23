// power_mode_auto_changer_v2.cpp

// #include <cstdio>
#include <iostream>
// #include <string>
// #include <memory>
// #include <stdexcept>
// #include <array>
#include "cli/parse-args.hpp"

int main(int argc, char *argv[])
{
    AppParams appParams = parseArgs(argc, argv);
    try
    {
        switch (appParams.action)
        {
        case AppAction::Help:
            std::cout << "Show help";
            break;
        case AppAction::Status:
            std::cout << "Show status";
            break;

        case AppAction::Version:
            std::cout << "Show version";
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