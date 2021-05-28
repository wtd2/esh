#include "esh.h"
#include "shell.h"

#include <iostream>
#include <string>
#include <regex>
#include <wait.h>
#include <fcntl.h>

using namespace std;

int main(int argc, char *argv[], const char *env[]) {
    Shell shell(env);

    while (shell.var.exit == 0) {
        shell.loop_shell();
    }
    
    return shell.var.return_value;
    
    // int help = dup(1);
    // int fd1[2];
    // // int fd2[2];
    // pipe(fd1);
    // dup2(fd1[1], 1);
    // int pid = fork();
    // if (pid){
    //     wait(NULL);
    // }else{
        
    //     execlp("ls", "ls", "/home/bt/", NULL);
    // }
    // close(fd1[1]);

    // dup2(fd1[0], 0);

    // pipe(fd1);
    // dup2(fd1[1], 1);

    // pid = fork();
    // if (pid){
    //     wait(NULL);
    // }else{
    //     execlp("cat", "cat",  NULL);
    // }
    // // close(0);
    // close(fd1[1]);

    // dup2(fd1[0], 0);
    // dup2(help, 1);
    // pid = fork();
    // if (pid){
    //     wait(NULL);
    // }else{        
    //     execlp("grep", "grep", "Do", NULL);
    // }
}