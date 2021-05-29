#include "esh.h"
#include "shell.h"
#include <stdio.h>
#include "exec.h"

#include <sys/types.h>
#include <sys/wait.h>
#include <fcntl.h>

bool Shell::is_builtin(char *cmd)
{
	return !(strcmp(cmd, "cd") * strcmp(cmd, "setenv") * strcmp(cmd, "unsetenv") * strcmp(cmd, "resetenv") * strcmp(cmd, "env") * strcmp(cmd, "kill") * strcmp(cmd, "history") * strcmp(cmd, "exit"));
}

void Shell::exit()
{
	this->var.exit = 1;
}

void Shell::exec_builtin(char *cmd, char *pram[])
{
	char *path = pram[1];
	if (!strcmp(cmd, "cd"))
	{
		if (!strcmp(path, "-"))
		{
			path = get_env_var(this->env.env, "OLDPWD");
		}
		if (!strcmp(path, "~"))
		{
			path = get_env_var(this->env.env, "HOME");
		}
		resetenv("OLDPWD", getcwd(NULL, NULL)); //TODO
		change_path(path);
		resetenv("PWD", getcwd(NULL, NULL)); //TODO
	}
	else if (!strcmp(cmd, "setenv"))
	{
		setenv(pram[1]);
	}
	else if (!strcmp(cmd, "unsetenv"))
	{
		unsetenv(pram[1]);
	}
	else if (!strcmp(cmd, "resetenv"))
	{
		resetenv(pram[1], pram[2]);
	}
	else if (!strcmp(cmd, "env"))
	{
		showenv();
	}
	// else if (!strcmp(cmd, "kill"))
	// {
	// 	esh_print_str("enter kill", 1)
	// 	esh_println_str(getcwd(NULL, NULL), 1);
	// {
	// 	// history();
	// }
	// else if (!strcmp(cmd, "exit"))
	// {
	// 	exit();
	// }
}