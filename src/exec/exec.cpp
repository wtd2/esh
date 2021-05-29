#include "esh.h"
#include "shell.h"
#include "exec.h"
#include "sig.h"

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

void signal_running(int sig)
{
	if (sig == SIGINT)
	{
		esh_println_str("", 1);
		signal(SIGINT, signal_running);
	}
}

int Shell::execute(Command *cmd, bool *last_pipe, int *fd)
{
	// printf("%s, %s, %s, %s, %s\n", cmd->path, cmd->in_file, cmd->out_file, cmd->error_file, cmd->sep);
	if (cmd->error_file) {
		int fd_err = open(cmd->error_file, O_RDWR | (cmd->append?O_APPEND:O_TRUNC));
		if (fd_err == -1)
			fd_err = open(cmd->error_file, O_CREAT | O_RDWR | O_TRUNC, 0644);
		dup2(fd_err, 2);
		close(fd_err);
	}

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
		int fd_out = open(cmd->out_file, O_RDWR | (cmd->append?O_APPEND:O_TRUNC));
		if (fd_out == -1)
			fd_out = open(cmd->out_file, O_CREAT | O_RDWR | O_TRUNC, 0644);
		dup2(fd_out, 1);
		close(fd_out);
	}
	else if (cmd->sep && cmd->sep[0] == '|')
	{
		// printf("use pipe\n");
		pipe(fd);
		dup2(fd[1], 1); // redirect out to pipe
		close(fd[1]);
		(*last_pipe) = true;
	}
	signal(SIGINT, signal_running);
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
			if (execvpe(cmd->path, cmd->argv, env.env)==-1) {
				esh_print_str("esh: ", 2);
				esh_println_str(strerror(errno), 2);
				exit(EXIT_FAILURE);
			}
		}
	}

	return 0;
}