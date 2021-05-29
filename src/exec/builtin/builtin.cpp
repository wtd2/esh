#include <fcntl.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/wait.h>

#include "esh.h"
#include "exec.h"
#include "shell.h"

bool Shell::is_builtin(char *cmd) {
  for (int i = 0; this->builtinList[i] != NULL; i++) {
    if (!strcmp(cmd, this->builtinList[i])) return 1;
  }
  return 0;
}

void Shell::shell_exit() { this->var.exit = 1; }

int Shell::check(char *cmd, int aim, int real) {
  if (aim < real) {
    esh_print_str("too many arguments: ", 2);
    esh_println_str(cmd, 2);
    return 1;
  } else if (aim > real) {
    esh_print_str("too few arguments: ", 2);
    esh_println_str(cmd, 2);
    return 1;
  }
  return 0;
}

void Shell::exec_builtin(char *cmd, char *pram[]) {
  int len = 0;
  while (pram[len] != NULL) len++;
  if (!strcmp(cmd, "cd")) {
    if (check(cmd, 2, len)) return;
    char *path = pram[1];
    if (!strcmp(path, "-")) {
      path = get_env_var(this->env.env, "OLDPWD");
    }
    if (!strcmp(path, "~")) {
      path = get_env_var(this->env.env, "HOME");
    }
    resetenv("OLDPWD", getcwd(NULL, 0));
    change_path(path);
    resetenv("PWD", getcwd(NULL, 0));
  } else if (!strcmp(cmd, "setenv")) {
    if (check(cmd, 2, len)) return;
    setenv(pram[1]);
  } else if (!strcmp(cmd, "unsetenv")) {
    if (check(cmd, 2, len)) return;
    unsetenv(pram[1]);
  } else if (!strcmp(cmd, "resetenv")) {
    if (check(cmd, 3, len)) return;
    resetenv(pram[1], pram[2]);
  } else if (!strcmp(cmd, "env")) {
    if (check(cmd, 1, len)) return;
    showenv();
  } else if (!strcmp(cmd, "history")) {
    if (check(cmd, 2, len)) return;
    _hist_entry **he = history_list();
    int len = 0;
    while (he[len] != NULL) len++;
    for (int i = 0; i < atoi(pram[1]) && i < len; i++) {
      esh_println_str(he[len - i - 1][0].line, 1);
    }
  } else if (!strcmp(cmd, "exit")) {
    shell_exit();
  }
}