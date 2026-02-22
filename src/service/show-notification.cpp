#include "show-notification.hpp"
#include "../common/command.hpp"
#include <string>
#include <unistd.h>
#include <vector>

void showNotification(const UserInfo &user,
                      const std::string &icon,
                      const std::string &message)
{
        std::string bus = "unix:path=/run/user/" + user.uid + "/bus";

        std::string payload =
            "{'icon': <'" + icon + "'>, 'label': <'" + message + "'>}";

        std::vector<std::string> args = {
            "sudo",
            "-u", user.name,
            "env",
            "DBUS_SESSION_BUS_ADDRESS=" + bus,
            "gdbus",
            "call",
            "--session",
            "--dest", "org.Cinnamon",
            "--object-path", "/org/Cinnamon",
            "--method", "org.Cinnamon.ShowOSD",
            payload};

        std::vector<char *> argv;
        for (auto &s : args)
                argv.push_back(s.data());
        argv.push_back(nullptr);

        execvp("sudo", argv.data());
}