#include "esh.h"
#include "shell.h"
#include "exec.h"

#include <string.h>

Command::Command(char *path, char *argv[]) {
    this->path = path;
    this->argv = argv;
}
