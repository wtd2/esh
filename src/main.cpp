#include "esh.h"
#include "shell.h"

#include <iostream>
#include <string>
#include <regex>

using namespace std;

int main(int argc, char *argv[], const char *env[]) {
    Shell shell(env);

    while (shell.var.exit == 0) {
        shell.loop_shell();
    }
    
    return shell.var.return_value;
}