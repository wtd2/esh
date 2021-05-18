#include "esh.h"
#include "shell.h"

#include <string.h>
#include <unistd.h>

int init_shell(struct s_esh *shell, const char *env[]) {
    /* init struct. */
    memset(shell, 0, sizeof(struct s_esh));

    /* init prompt. */

    /* init var. */

    /* init env. */
	shell->env.env = esh_cpy_arr(env);
    shell->env.oldpwd = NULL;

    /* success. */
    return 0;
}