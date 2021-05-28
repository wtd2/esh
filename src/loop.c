#include "esh.h"
#include "exec.h"
#include "shell.h"
#include "prompt.h"

#define BUFFER_SIZE 2048

void loop_shell(struct s_esh *shell) {
    char line[BUFFER_SIZE] = "";
    prompt_input(shell, line); // read input into line

    //echo line
    esh_println_str(line, 1);
}