#ifndef SHELL_H
#define SHELL_H

#include <stdlib.h>
#include <stdbool.h>
#include <stdint.h>

struct s_prompt {

};

struct s_var {
    bool exit;
    uint8_t return_value;
};

struct s_env {
    char **env;
    char *oldpwd;
};

struct s_esh {
    struct s_prompt prompt;
    struct s_var var;
    struct s_env env;
};

int init_shell(struct s_esh *shell, const char *env[]);
void free_shell(struct s_esh *shell);

#endif