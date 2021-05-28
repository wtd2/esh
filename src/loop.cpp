#include "esh.h"
#include "exec.h"
#include "shell.h"
#include "prompt.h"
#include "parse.h"

#include <sys/types.h>
#include <sys/wait.h>

#define BUFFER_SIZE 2048

char* command_generator (char *text, int state) {
  printf("text=%s, state=%d\n", text, state);
  if (state==0) { // init

  }
  
  return (char*) NULL;
}

char **completer (char *text, int start, int end)
{
  printf("text=%s, start=%d, end=%d\n", text, start, end);
  char **matches;
  esh_println_str(text, 1);
  matches = (char **)NULL;

  /* If this word is at the start of the line, then it is a command
     to complete.  Otherwise it is the name of a file in the current
     directory. */
  if (start == 0)
    matches = rl_completion_matches (text, (rl_compentry_func_t*)command_generator);

  return (matches);
}



void Shell::loop_shell() {
    char line[BUFFER_SIZE] = "";
    prompt_input(line); // read input into line
  
    add_history(line);
    
    // // echo line
    esh_println_str(line, 1);
    
    // tokenize and parse line into commands
    vector<Command*> cmds = parse(line);
    
    for (int i=0; i<cmds.size(); ++i) {
        printf("%s", cmds[i]->path);
        for (int j=0; cmds[i]->argv[j]; j++) {
            printf(", %s", cmds[i]->argv[j]);
        }
        printf("\n");

        int pid = fork();
        if (pid) {
            wait(NULL);
        }else{
            execvpe(cmds[i]->path, cmds[i]->argv, env.env);
        }
        delete cmds[i];
    }
}