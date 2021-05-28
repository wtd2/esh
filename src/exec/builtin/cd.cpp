
#include "esh.h"
#include "shell.h"

#include <string.h>
#include <unistd.h>
#include <stdio.h>

void Shell::change_path(char *path)
{
	char	*tmp_path;

	if (path == NULL)
	{
		esh_println_str(": No such file or directory.", 2);
	}
	tmp_path = getcwd(NULL, 1000);

    
	if (chdir(path) != 0)
	{
		esh_println_str(path, 2);
	}
	else
	{
		// ft_strdel(&tcsh->env.oldpwd);
		// tcsh->env.oldpwd = tmp_path;
	}
}