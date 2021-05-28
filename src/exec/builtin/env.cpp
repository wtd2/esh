#include "esh.h"
#include "shell.h"

#include <string.h>
#include <unistd.h>
#include <stdio.h>

void showenv(struct s_esh *shell)
{
    int len=0;
    while(shell->env.env[len] != NULL) len++;
    for(int i=0;i<len;++i)
    {
        esh_println_str(shell->env.env[i],1);
    }
}

void setenv(struct s_esh *shell, char *newenv)
{
    int len=0;
    while(shell->env.env[len] != NULL) len++;
    char** new_env = (char**)malloc(sizeof(char*) * (len + 2));
    for (int i = 0; i < len; i++) {
        new_env[i] = shell->env.env[i];
    }
    strcpy(new_env[len], newenv);
    shell->env.env = new_env;
}

void unsetenv(struct s_esh *shell, char *name)
{
    int len=0;
    int c=0;
    while(shell->env.env[len] != NULL) len++;
    int id =get_env_var_no(shell->env.env,name);
    char** new_env = (char**)malloc(sizeof(char*) * (len));
    for(int i=0;i<len;++i)
    {
        if(i!=id)
        {
            new_env[c]=shell->env.env[i];
            ++c;
        }
    }
    shell->env.env=new_env;
}

void resetenv(struct s_esh *shell, char *name,char *value)
{
    int len=0;
    while(shell->env.env[len] != NULL) len++;
    int id =get_env_var_no(shell->env.env, name);
    
    if (id == -1) {
        return;
    }
    // char** new_env = (char**)malloc(sizeof(char*) * (len+1));
    shell->env.env[id] = strdup(name);
    strcat(shell->env.env[id], "=");
    strcat(shell->env.env[id], value);
    // for(int i=0;i<len;++i)
    // {
    //     if(i!=id)s
    //     {
    //         shell[i]=shell->env.env[i];
    //     }else
    //     {
    //     esh_println_str(name,1);
    //     esh_println_str(id,1);
    //     new_env[i]=value;
    //     esh_println_str(new_env[i],1);
    //     }
    // }
    // shell->env.env=new_env;
}
