#include "user.hpp"
#include "../common/command.hpp"
#include <stdexcept>
#include <iostream>

UserInfo getUser()
{
    UserInfo user;
    user.name = execCommand("loginctl list-sessions --no-legend | awk '{print $3}' | head -n1");
    user.uid = execCommand("id -u \"" + user.name + "\"");
    return user;
}