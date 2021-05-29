#include "esh.h"
#include "exec.h"
#include "shell.h"
#include "parse.h"

#define BUFFER_SIZE 2048


void Shell::loop_shell() {
	char line[BUFFER_SIZE] = "";
	prompt_input(line); // read input into line

	add_history(line);

	// tokenize and parse line into commands
	vector<Command*> cmds = parse(line);
	bool last_pipe= false;
	int fd[2]={0,1};
    for (int i=0; i<cmds.size(); ++i) {
            execute(cmds[i], &last_pipe, fd);
		    reset_fd();
//         delete cmds[i];
    }
}