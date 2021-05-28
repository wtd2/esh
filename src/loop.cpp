#include "esh.h"
#include "exec.h"
#include "shell.h"
#include "prompt.h"
#include "parse.h"

#define BUFFER_SIZE 2048

void loop_shell(struct s_esh *shell) {
    char line[BUFFER_SIZE] = "";
    prompt_input(shell, line); // read input into line
    add_history(line);
    
    // echo line
    esh_println_str(line, 1);
    
    // tokenize and parse line into commands
    vector<Command> cmds = parse(line);
    for (int i=0; i<cmds.size(); ++i) {
        printf("%s", cmds[i].path);
        for (int j=0; cmds[i].argv[j]; j++) {
            printf(", %s", cmds[i].argv[j]);
        }
        printf("\n");
    }
}