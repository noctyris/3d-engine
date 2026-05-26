#ifndef LOG_H
#define LOG_H

#include <stdio.h>

#define BLACK   "\033[1;30m"  // For background
#define RED     "\033[1;31m"  // colors, use the
#define GREEN   "\033[1;32m"  // same numbers
#define YELLOW  "\033[1;33m"  // (those from 30
#define BLUE    "\033[1;34m"  // to 39), but add
#define PURPLE  "\033[1;35m"  // ten to the number
#define AQUA    "\033[1;36m"  // to put it in [30;39]
#define GRAY1   "\033[1;37m"
#define GRAY2   "\033[1;38m"
#define WHITE   "\033[1;39m"
#define RESET   "\033[0m"
#define BOLD    "\033[1m"

void perrorf(const char *message, const char *err);

#endif
