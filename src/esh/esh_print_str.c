#include "esh.h"

#include <string.h>
#include <unistd.h>

void esh_print_str(char const *s, int fd) {
    write(fd, s, strlen(s));
}