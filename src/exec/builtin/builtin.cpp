#include <string.h>
#include "esh.h"
#include "builtin.h"
#include "shell.h"
#include <stdio.h>

bool is_builtin(char *cmd)
{
	return !(strcmp(cmd, "cd") *strcmp(cmd, "setenv") *strcmp(cmd, "unsetenv")*strcmp(cmd, "resetenv") *strcmp(cmd, "env") *strcmp(cmd, "kill") *strcmp(cmd, "history") *strcmp(cmd, "exit")); 
}

void exec_builtin(struct s_esh *shell, char *cmd, char *pram[])
{
	char *path=pram[1];
	if (!strcmp(cmd, "cd") ) 
	{
			if (!strcmp(path,"-"))
	{
		path=get_env_var(shell->env.env,"OLDPWD");
	}
	if (!strcmp(path,"~"))
	{
		path=get_env_var(shell->env.env,"HOME");
	}
		resetenv(shell,"OLDPWD",getcwd(NULL,NULL));//TODO
		change_path(shell,path);
		resetenv(shell,"PWD",getcwd(NULL,NULL));//TODO
		esh_println_str(getcwd(NULL,NULL),1);

		// chdir("/");
		// esh_println_str(getcwd(NULL,NULL),1);
	}
	else if (!strcmp(cmd, "setenv") ) 
	{
		setenv(shell,pram[1]);
	}
	else if (!strcmp(cmd, "unsetenv") ) 
	{
		unsetenv(shell,pram[1]);
	}
	else if (!strcmp(cmd, "resetenv") ) 
	{
		resetenv(shell,pram[1],pram[2]);
	}
	else if (!strcmp(cmd, "env") ) 
	{
		showenv(shell);
	}
	else if (!strcmp(cmd, "kill") ) 
	{
	esh_print_str("enter kill",1);
		// esh_kill(pram[0]);
	}
	else if (!strcmp(cmd, "history") ) 
	{
		history();
	}
	else if (!strcmp(cmd, "exit") ) 
	{
		exit(shell);
	}
}