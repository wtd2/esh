#include "esh.h"
#include "shell.h"
#include "prompt.h"

#include <string.h>

void prompt_display(struct s_esh *shell) {
    char* home_var = get_env_var(shell->env.env, "HOME");
    char* username_var = get_env_var(shell->env.env, "LOGNAME");
    char* pwd_var = get_env_var(shell->env.env, "PWD");
    char* prompt_str = strdup("");
    if (home_var != NULL && username_var != NULL && pwd_var != NULL) {
        strcat(prompt_str, "[\e[1;32m");
        strcat(prompt_str, username_var);
        strcat(prompt_str, "\e[0m:\e[34m");
        if (strstr(pwd_var, home_var) == pwd_var) {
            strcat(prompt_str, "~");
            strcat(prompt_str, &pwd_var[strlen(home_var)]);
        } else {
            strcat(prompt_str, pwd_var);
        }
        strcat(prompt_str, "\e[0m]");
    }
    strcat(prompt_str, "$ ");
    esh_print_str(prompt_str, 1);
    esh_free_str(&prompt_str);
}