#include "esh.h"
#include "shell.h"
#include "prompt.h"

void loop_shell(struct s_esh *shell) {
    char* raw = NULL;
    if (shell->var.is_a_tty)
        prompt_display(shell);
    int ret_value = prompt_input(shell, &raw);
    if (ret_value != 0) {
        if (ret_value == -1)
            shell->var.return_value = 1;
        shell->var.exit = 1;
        esh_free_str(&raw);
        return;
    }
    esh_println_str(raw, 1);
    esh_free_str(&raw);
}