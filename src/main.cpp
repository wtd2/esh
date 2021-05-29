#include "esh.h"
#include "fcntl.h"
#include "shell.h"

using namespace std;

int main(int argc, char *argv[], const char *env[]) {
  Shell shell(env);
  read_history(NULL);

  while (shell.var.exit == 0) {
    shell.loop_shell();
  }

  write_history(NULL);
  return shell.var.return_value;
}