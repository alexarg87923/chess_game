#include "helper.hpp"

std::string get_working_dir() {
    char buffer[FILENAME_MAX];
    if (getcwd(buffer, sizeof(buffer)) != nullptr) {
        return std::string(buffer);
    } else {
        std::cerr << "Failed to get the current working directory." << std::endl;
        return "";
    }
}