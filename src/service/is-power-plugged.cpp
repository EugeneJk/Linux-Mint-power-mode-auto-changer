#include "is-power-plugged.hpp"
#include "../common/command.hpp"
#include <stdexcept>
#include <iostream>

bool isPowerPlugged(const std::string &devicePath)
{
    FILE *file = fopen(devicePath.c_str(), "r");
    char status = fgetc(file);
    fclose(file);

    return status == '1';
}