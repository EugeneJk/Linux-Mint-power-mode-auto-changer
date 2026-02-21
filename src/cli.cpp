// power_mode_auto_changer_v2.cpp

#include <iostream>
#include <string>
#include <cstdio>
#include <memory>
#include <stdexcept>
#include <array>

int main(int argc, char* argv[]) {

    // Печать аргументов
    std::cout << "Arguments (" << argc - 1 << "):\n";
    for (int i = 1; i < argc; ++i) {
        std::cout << "  argv[" << i << "] = " << argv[i] << "\n";
    }

    const char* cmd = "echo \"test\"";

    std::array<char, 256> buffer;
    std::string result;

    FILE* pipe = popen(cmd, "r");
    if (!pipe) {
        std::perror("popen failed");
        return 1;
    }

    while (fgets(buffer.data(), buffer.size(), pipe) != nullptr) {
        result += buffer.data();
    }

    if (pclose(pipe) == -1) {
        std::perror("pclose failed");
        return 1;
    }

    // Печать полностью сформированной строки
    std::cout << "Command result:\n" << result;

    return 0;
}