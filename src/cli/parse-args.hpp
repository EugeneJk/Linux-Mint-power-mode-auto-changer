#ifndef CLI_PARSE_ARGS_HPP
#define CLI_PARSE_ARGS_HPP

#include <string>

/* Power Profile types */
enum class AppAction
{
    Help,
    Status,
    InteractiveConfig,
    MenuInteractiveConfig,
    Version
};


/* Trim string utility*/
AppAction extractAction(int argc, char* argv[]);

#endif