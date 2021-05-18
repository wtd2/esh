#include "esh.h"
#include "shell.h"

int main(int argc, char *argv[], const char *env[]) {
    struct s_esh shell;
    if (init_shell(&shell, env) == 0) {
        while (shell.var.exit == 0) {
        //    loop_shell(&shell);
            if (shell.env.env != NULL) {
                int i = 0;
                while(shell.env.env[i] != NULL) {
                    esh_println_str(shell.env.env[i], 1);
                    i++;
                }
            }
	        break;
        }
    }
    free_shell(&shell);
    return shell.var.return_value;
}