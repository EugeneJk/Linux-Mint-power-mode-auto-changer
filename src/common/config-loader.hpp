#ifndef COMMON_CONFIG_LOADER_HPP
#define COMMON_CONFIG_LOADER_HPP

#include <string>
#include <map>

/* Load configuration file */
std::map<std::string, std::string> loadConfig(const std::string &path);

#endif