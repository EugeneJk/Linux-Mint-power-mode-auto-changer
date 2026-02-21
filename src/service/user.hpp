#ifndef SERVICE_USER_HPP
#define SERVICE_USER_HPP

#include <string>

struct UserInfo {
    std::string name;
    int uid;
};

UserInfo getUser();  // может выбросить std::runtime_error

#endif