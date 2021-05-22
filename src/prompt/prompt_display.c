#include "esh.h"
#include "shell.h"
#include "prompt.h"

#include <string.h>

#define BUFFER_SIZE 1024

void get_prompt_str(struct s_esh *shell, char* prompt_str) {
    char* home_var = get_env_var(shell->env.env, "HOME");
    char* username_var = get_env_var(shell->env.env, "LOGNAME");
    char* pwd_var = get_env_var(shell->env.env, "PWD");
    if (home_var != NULL && username_var != NULL && pwd_var != NULL) {
        strcat(prompt_str, "[\e[1;32m");
        strcat(prompt_str, username_var);
        strcat(prompt_str, "\e[0m:\e[34m");
        if (strstr(pwd_var, home_var) == pwd_var) {
            strcat(prompt_str, "%~");
            strcat(prompt_str, &pwd_var[strlen(home_var)]);
        } else {
            strcat(prompt_str, pwd_var);
        }
        strcat(prompt_str, "\e[0m]");
    }
}