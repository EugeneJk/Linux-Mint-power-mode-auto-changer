#include "is-cinnamon-osd.hpp"

#include <string>
#include <cstdio>
#include <unistd.h>

bool hasCinnamonOSD(const UserInfo& user)
{
    std::string bus = "unix:path=/run/user/" + user.uid + "/bus";

    bool isRootContext = (geteuid() == 0);

    std::string cmd;

    if (isRootContext)
    {
        cmd =
            "sudo -u " + user.name +
            " env DBUS_SESSION_BUS_ADDRESS=" + bus +
            " gdbus introspect --session "
            "--dest org.Cinnamon "
            "--object-path /org/Cinnamon 2>/dev/null";
    }
    else
    {
        cmd =
            "env DBUS_SESSION_BUS_ADDRESS=" + bus +
            " gdbus introspect --session "
            "--dest org.Cinnamon "
            "--object-path /org/Cinnamon 2>/dev/null";
    }

    FILE* pipe = popen(cmd.c_str(), "r");
    if (!pipe)
    {
        return false;
    }

    std::string output;
    char buffer[256];

    while (fgets(buffer, sizeof(buffer), pipe) != nullptr)
    {
        output += buffer;
    }

    int rc = pclose(pipe);

    return rc == 0 &&
           output.find("ShowOSD") != std::string::npos;
}