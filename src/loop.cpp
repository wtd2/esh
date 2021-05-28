#include "esh.h"
#include "exec.h"
#include "shell.h"
#include "parse.h"

#include <sys/types.h>
#include <sys/wait.h>
#include <fcntl.h>

#define BUFFER_SIZE 2048

int execute(Command *cmd, bool* last_pipe, int* fd) {
	printf("%s, %s, %s, %s\n", cmd->path, cmd->in_file, cmd->out_file, cmd->sep);
	
	if (cmd->in_file!=NULL) { // redirect in from file
		int fd_in = open(cmd->in_file, O_RDONLY);
		if (fd_in==-1) {
			return -1;
		}
		dup2(fd_in, 0);
	}else if ((*last_pipe)) dup2(fd[0], 0); // redirect in from pipe
	
	(*last_pipe) = false;
	if (cmd->out_file!=NULL) {
		printf("output to file\n");
		int fd_out = open(cmd->out_file, O_RDWR | O_TRUNC);
		if (fd_out==-1) fd_out = open(cmd->out_file, O_CREAT | O_RDWR | O_TRUNC, 0644);
		dup2(fd_out, 1);
		close(fd_out);
	}else if(cmd->sep && cmd->sep[0]=='|') {
		printf("use pipe\n");
		pipe(fd);
		dup2(fd[1], 1); // redirect out to pipe
		close(fd[1]);
		(*last_pipe) = true;
	}
	int pid = fork();
	if (pid){
		wait(NULL);
	}else{
		execvp(cmd->path, cmd->argv);
	}

	if (cmd->in_file) close(0);
	return 0;
}

void Shell::loop_shell() {
	char line[BUFFER_SIZE] = "";
	prompt_input(line); // read input into line

	add_history(line);

	// // echo line
	esh_println_str(line, 1);

	// tokenize and parse line into commands
	vector<Command*> cmds = parse(line);
	bool last_pipe= false;
	int fd[2]={0,1};
    for (int i=0; i<cmds.size(); ++i) {
		execute(cmds[i], &last_pipe, fd);
		reset_fd();
	}
}