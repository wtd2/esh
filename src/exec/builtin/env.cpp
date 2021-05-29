#include "esh.h"
#include "shell.h"
#include "string.h"
#include "unistd.h"

void Shell::showenv() {
  int len = 0;
  while (env.env[len] != NULL) len++;
  for (int i = 0; i < len; ++i) {
    esh_println_str(env.env[i], 1);
  }
}

void Shell::setenv(char *newenv) {
  int len = 0;
  while (env.env[len] != NULL) len++;
  env.env = (char **)realloc(env.env, sizeof(char *) * (len + 1));
  env.env[len] = strdup(newenv);
}

void Shell::unsetenv(char *name) {
  int len = 0;
  while (env.env[len] != NULL) len++;
  int id = get_env_var_no(env.env, name);
  if (id == -1) {
    esh_println_str("No such env", 2);
    return;
  }
  env.env[id] = env.env[len - 1];
  esh_free_str(&env.env[len - 1]);
  env.env[len - 1] = NULL;
}

void Shell::resetenv(const char *name, char *value) {
  int len = 0;
  while (env.env[len] != NULL) len++;
  int id = get_env_var_no(env.env, name);

  if (id == -1) {
    esh_println_str("No such env", 2);
    return;
  }
  env.env[id] = strdup(name);
  strcat(env.env[id], "=");
  strcat(env.env[id], value);
}
