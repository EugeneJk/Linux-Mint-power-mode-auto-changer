#include <iostream>
#include "service/user.hpp"

int main() {

    std::cout << "Switch power mode service\n";

    try {
        std::cout << "Get user\n";
        UserInfo user = getUser();
        std::cout << "User: " << user.name << " (uid=" << user.uid << ")\n";
    }
    catch (const std::exception& ex) {
        std::cerr << "Error: " << ex.what() << "\n";
        return 1;
    }

    std::cout << "Check config\n";
    std::cout << "Get current power profile\n";
    std::cout << "Check with new profile\n";
    std::cout << "Switch profile if needed\n";
    std::cout << "Show notification if needed\n";

    return 0;
}