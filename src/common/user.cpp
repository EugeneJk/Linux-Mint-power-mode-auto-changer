#include "user.hpp"
#include "../common/command.hpp"
#include <stdexcept>
#include <iostream>

UserInfo getUser()
{
    // Базовая заглушка
    bool simulateError = false;

    if (simulateError)
    {
        throw std::runtime_error("Failed to get user");
    }

    UserInfo user;
    user.name = execCommand("loginctl list-sessions --no-legend | awk '{print $3}' | head -n1");
    user.uid = execCommand("id -u \"" + user.name + "\"");
    return user;
}