#include "esh.h"
#include "shell.h"
#include "prompt.h"

#include <readline/readline.h>
#include <readline/history.h>

#define BUFFER_SIZE 128

/*
    Just assume is_a_tty is always true.
*/
void loop_shell(struct s_esh *shell) {
    char* prompt_str = (char*)malloc(BUFFER_SIZE);
    char* line;
    
    get_prompt_str(shell, prompt_str);
    line = readline(prompt_str);
    free(prompt_str);
    
    // if (ret_value != 0) {
    //     if (ret_value == -1)
    //         shell->var.return_value = 1;
    //     shell->var.exit = 1;
    //     esh_free_str(&raw);
    //     return;
    // }
    
    esh_println_str(line, 1);
    add_history(line);
    free(line);
}