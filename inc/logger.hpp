#ifndef LOGGER_HPP
#define LOGGER_HPP

#include <string>
#include <iostream>

#define BLACK   "\033[1;30m"
#define RED     "\033[1;31m"
#define GREEN   "\033[1;32m"
#define YELLOW  "\033[1;33m"
#define BLUE    "\033[1;34m"
#define PURPLE  "\033[1;35m"
#define AQUA    "\033[1;36m"
#define WHITE   "\033[1;39m"
#define RESET   "\033[0m"
#define BOLD    "\033[1m"

class Logger {
public:
    static void error(const std::string& message, const std::string& err = "");
};

#endif
