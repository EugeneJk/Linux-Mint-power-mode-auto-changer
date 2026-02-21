#include "config-loader.hpp"
#include <fstream>
#include <string>
#include <map>
#include <sstream>
#include <stdexcept>

std::map<std::string, std::string> loadConfig(const std::string &path)
{
    std::ifstream file(path);
    if (!file)
        throw std::runtime_error("Cannot open config");

    std::map<std::string, std::string> config;
    std::string line;

    while (std::getline(file, line))
    {
        // пропустить пустые строки и комментарии
        if (line.empty() || line[0] == '#')
            continue;

        std::istringstream iss(line);
        std::string key, value;
        if (std::getline(iss, key, '=') && std::getline(iss, value))
        {
            config[key] = value;
        }
    }

    return config;
}