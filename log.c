#include "log.h"

void perrorf(const char *message, const char *err) {
  fprintf(stderr, RED BOLD "[-] Error: " RESET RED "%s: %s\n" RESET, message, err);
}
