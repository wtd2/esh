#include "esh.h"

void esh_println_str(char const *s, int fd) {
    esh_print_str(s, fd);
    esh_print_str("\n", fd);
}