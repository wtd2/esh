
#include <stdio.h>
#include <string.h>
#include <unistd.h>

#include "esh.h"
#include "shell.h"

void Shell::change_path(char *path) {
  char *tmp_path;

  if (path == NULL) {
    esh_println_str(": No such file or directory.", 2);
  }
  tmp_path = getcwd(NULL, 0);

  if (chdir(path) != 0) {
    esh_println_str(path, 2);
  }
}