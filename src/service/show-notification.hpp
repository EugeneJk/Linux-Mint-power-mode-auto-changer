#ifndef SERVICE_SHOW_NOTIFICATION_HPP
#define SERVICE_SHOW_NOTIFICATION_HPP

#include "../common/user.hpp"
#include <string>

/* Get is power plugged */
void showNotification(const UserInfo &user, const std::string &icon, const std::string &message);

#endif