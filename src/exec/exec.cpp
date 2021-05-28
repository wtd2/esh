#include "esh.h"
#include "shell.h"
#include "exec.h"

#include <string.h>
#include <stdio.h>

Command::Command(char *path, char *argv[]) {
    this->path = path;
    this->argv = argv;
}

Command::~Command() {
    // printf("destruct cmd %s\n", path);
    esh_free_str(&path);
    esh_free_str_arr(&argv);
}