#include "esh.h"
#include "sig.h"
#include "shell.h"

void signal_running(int sig) {
    if (sig == SIGINT) {
        esh_println_str("", 1);
        signal(SIGINT, signal_running);
    }
}

void signal_shell(int sig) {
    if (sig == SIGINT) {
        esh_println_str("", 1);
        // prompt_input(line);
        signal(SIGINT, signal_shell);
    }
}
