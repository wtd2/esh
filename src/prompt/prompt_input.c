#include "esh.h"
#include "shell.h"
#include "prompt.h"

#include <string.h>
#include <unistd.h>

/* 
    this is a temporary function needs enhancement
    may lead to memory leak
*/
#define BUFFER_SIZE 1024

// int prompt_input(struct s_esh *shell, char **raw) {
    
//     (*raw) = malloc(BUFFER_SIZE);
//     read(0, (*raw), BUFFER_SIZE - 1);
//     char *c = strchr((*raw), '\n');
//     if (c != NULL) *c = 0;
//     if (strcmp((*raw), "exit") == 0) {
//         return 1;
//     }

//     /* success. */
//     return 0;

//     /* exit. */
//     return 1;

//     /* failed. */
//     return -1;
// }

int prompt_make_str(struct s_esh *shell, char *prompt_str){
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
    return 0; //success
}

int prompt_input(struct s_esh *shell, char *line) {
    char prompt_str[BUFFER_SIZE]="";
    char *raw;

    prompt_make_str(shell, prompt_str);
    raw = readline(prompt_str);
    while (raw[strlen(raw)-1]=='\\') {
        strncat(line, raw, strlen(raw)-1);
        esh_free_str(&raw);
        raw = readline("> ");
    }
    strcat(line, raw);
    esh_free_str(&raw);
    return 0; //success
}