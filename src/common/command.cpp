#include "command.hpp"
#include <cstdio>
#include <array>
#include <stdexcept>
#include <string>

std::string execCommand(const std::string &command)
{
    std::array<char, 256> buffer;
    std::string result;

    FILE *pipe = popen(command.c_str(), "r");
    if (!pipe)
    {
        throw std::runtime_error("popen failed");
    }

    while (fgets(buffer.data(), buffer.size(), pipe) != nullptr)
    {
        result += buffer.data();
    }

    if (pclose(pipe) == -1)
    {
        throw std::runtime_error("pclose failed");
    }

    // Удаляем завершающие \n и \r
    while (!result.empty() &&
           (result.back() == '\n' || result.back() == '\r'))
    {
        result.pop_back();
    }

    return result;
}