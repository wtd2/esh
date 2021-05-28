#include "esh.h"
#include "exec.h"
#include "shell.h"
#include "prompt.h"
#include "parse.h"
#include "builtin.h"

#include <wait.h>
#define BUFFER_SIZE 2048

void loop_shell(struct s_esh *shell) {
    char line[BUFFER_SIZE] = "";
    prompt_input(shell, line); // read input into line
    add_history(line);

    // echo line
    esh_println_str(line, 1);
    
    // tokenize and parse line into commands
    vector<Command*> cmds = parse(line);
    
    for (int i=0; i<cmds.size(); ++i) {

        if (is_builtin(cmds[i]->path)) {
            exec_builtin(shell,cmds[i]->path,cmds[i]->argv);
        } else {
            int pid = fork();
            if (pid) wait(NULL);
            else execvpe(cmds[i]->path, cmds[i]->argv, shell->env.env);
        }
        
        
        // delete cmds[i];
    }
}