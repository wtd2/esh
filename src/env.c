#include "esh.h"
#include "shell.h"

#include <string.h>
#include <stdio.h>

int get_env_var_no(char **env, const char *name) {
    int i = 0;
    char* equal_name = strdup(name);
    strcat(equal_name, "=");
    while (env[i] != NULL) {
        if (strstr(env[i], equal_name) == env[i]) {
        	esh_free_str(&equal_name);
            return i;
        }
        i++;
    }
	esh_free_str(&equal_name);
    return -1;
}

char *get_env_var(char **env, const char *name) {
    int pos = get_env_var_no(env, name);
    if (pos == -1)
        return NULL;
    return &env[pos][strlen(name) + 1];
}