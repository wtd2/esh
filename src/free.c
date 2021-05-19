#include "esh.h"
#include "shell.h"

void free_shell(struct s_esh *shell) {
    /* show prompt. */
    if (shell->var.is_a_tty)
        esh_print_str("exit\n", 1);
    
    /* free prompt. */

    /* free var. */

    /* free env. */
	esh_free_str_arr(&shell->env.env);
    // esh_free_str(&shell->env.oldpwd);
}