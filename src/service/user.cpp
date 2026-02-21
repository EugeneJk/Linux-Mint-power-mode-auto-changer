#include "user.hpp"
#include <stdexcept>

UserInfo getUser() {
    // Базовая заглушка
    bool simulateError = false;

    if (simulateError) {
        throw std::runtime_error("Failed to get user");
    }

    UserInfo user;
    user.name = "testuser";
    user.uid = 1000;

    return user;
}