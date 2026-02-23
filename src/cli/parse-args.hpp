#ifndef CLI_PARSE_ARGS_HPP
#define CLI_PARSE_ARGS_HPP

#include <string>

/* Power Profile types */
enum class AppAction
{
    Help,
    Status,
    InteractiveConfig,
    Version
};

/*  App params */
struct AppParams
{
    AppAction action;
    std::string lang;
};

/* Trim string utility*/
AppParams parseArgs(int argc, char* argv[]);

#endif