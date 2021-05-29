#include "esh.h"
#include "shell.h"
#include "exec.h"

#include <string.h>
#include <stdio.h>
#include <fcntl.h>
#include <sys/wait.h>

Command::Command(
    char *path, 
    char *argv[], 
    char *sep,
    char *in_file,
    char *out_file,
    char *error_file,
    bool append) {

    this->path = path;
    this->argv = argv;
    this->sep = sep;
    this->in_file = in_file;
    this->out_file = out_file; this->append = append;
    this->error_file = error_file;
}

Command::~Command() {
    // printf("destruct cmd %s\n", path);
    esh_free_str(&path);
    esh_free_str_arr(&argv);
}

int Shell::execute(Command *cmd, bool *last_pipe, int *fd)
{
	printf("%s, %s, %s, %s\n", cmd->path, cmd->in_file, cmd->out_file, cmd->sep);

	if (cmd->in_file != NULL)
	{ // redirect in from file
		int fd_in = open(cmd->in_file, O_RDONLY);
		if (fd_in == -1)
		{
            esh_println_str("error: No such file or directory", 2);
			return -1;
		}
		dup2(fd_in, 0);
	}
	else if ((*last_pipe))
		dup2(fd[0], 0); // redirect in from pipe

	(*last_pipe) = false;
	if (cmd->out_file != NULL)
	{
		printf("output to file %s, append=%d\n", cmd->out_file, cmd->append);
		int fd_out = open(cmd->out_file, O_RDWR | (cmd->append?O_APPEND:O_TRUNC));
		if (fd_out == -1)
			fd_out = open(cmd->out_file, O_CREAT | O_RDWR | O_TRUNC, 0644);
		dup2(fd_out, 1);
		close(fd_out);
	}
	else if (cmd->sep && cmd->sep[0] == '|')
	{
		printf("use pipe\n");
		pipe(fd);
		dup2(fd[1], 1); // redirect out to pipe
		close(fd[1]);
		(*last_pipe) = true;
	}
	if (is_builtin(cmd->path))
	{
		exec_builtin(cmd->path, cmd->argv);
	}
	else
	{
		int pid = fork();
		if (pid)
		{
			wait(NULL);
		}
		else
		{
			if (execvpe(cmd->path, cmd->argv, env.env)==-1){
				esh_println_str(strerror(errno), 2);
			}
		}
	}

	if (cmd->in_file)
		close(0);
	return 0;
}