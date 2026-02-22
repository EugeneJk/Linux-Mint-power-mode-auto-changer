#ifndef COMMON_SYSTEM_CONFIG_HPP
#define COMMON_SYSTEM_CONFIG_HPP

#include <string>
#include <map>
#include <optional>

/* System configuration struct */
struct SystemConfig
{
    std::string acStatusContainer;
};

/* Parses user configuration */
SystemConfig parceSystemConfig(const std::map<std::string, std::string> &config);


#endif