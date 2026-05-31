#include "logger.hpp"

void Logger::error(const std::string& message, const std::string& err) {
    std::cerr << RED << BOLD << "[-] Error: " << RESET << RED << message;
    if (!err.empty()) {
        std::cerr << ": " << err;
    }
    std::cerr << RESET << std::endl;
}
