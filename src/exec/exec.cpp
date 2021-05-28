#include "esh.h"
#include "shell.h"
#include "exec.h"

#include <string.h>
#include <stdio.h>

Command::Command(
    char *path, 
    char *argv[], 
    char *sep,
    char *in_file,
    char *out_file) {

    this->path = path;
    this->argv = argv;
    this->sep = sep;
    this->in_file = in_file;
    this->out_file = out_file;
}

Command::~Command() {
    printf("destruct cmd %s\n", path);
    esh_free_str(&path);
    esh_free_str_arr(&argv);
}