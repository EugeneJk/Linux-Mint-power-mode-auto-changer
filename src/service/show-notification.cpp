#include "show-notification.hpp"
#include "../common/constants.hpp"
#include "../common/command.hpp"
#include <string>
#include <unistd.h>
#include <vector>
#include <iostream>
#include <sys/wait.h>

void showCinnamonNotification(const UserInfo &user,
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

    pid_t pid = fork();

    if (pid == 0)
    {
        // child
        execvp("sudo", argv.data());
        throw std::runtime_error("Notification display failed");
    }

    int status = 0;
    waitpid(pid, &status, 0);
}

void showDefaultNotification(const UserInfo &user,
                          const std::string &icon,
                          const std::string &message)
{
    std::string bus = "unix:path=/run/user/" + user.uid + "/bus";

    std::vector<std::string> args = {
        "sudo",
        "-u", user.name,
        "env",
        "DBUS_SESSION_BUS_ADDRESS=" + bus,
        "DISPLAY=:0",
        "notify-send",
        "-i", icon,
        "-t", "3000",
        "-h", "string:x-canonical-private-synchronous:" + APP_NAME,
        message,
        APP_NAME
    };

    std::vector<char *> argv;
    for (auto &s : args)
        argv.push_back(s.data());
    argv.push_back(nullptr);

    pid_t pid = fork();

    if (pid == 0)
    {
        // child
        execvp("sudo", argv.data());
        throw std::runtime_error("Notification display failed");
    }

    int status = 0;
    waitpid(pid, &status, 0);
}

void showNotification(const UserInfo &user,
                      const std::string &icon,
                      const std::string &message,
                      bool isCinnamon
                    )
{

    if (isCinnamon)
    {
        showCinnamonNotification(user, icon, message);
    }
    else
    {
        showDefaultNotification(user, icon, message);
    }
}