#ifndef COMMON_USER_HPP
#define COMMON_USER_HPP

#include <string>

/*  User info data */
struct UserInfo
{
    std::string name;
    std::string uid;
};

/* Get system user name and id */
UserInfo getUser();

#endif