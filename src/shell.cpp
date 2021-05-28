#include "esh.h"
#include "shell.h"

#include <dirent.h>
#include <string.h>

Shell::Shell(const char *env[]) {
    this->var.exit = 0;
    this->var.is_a_tty = isatty(0);
    this->env.env = esh_cpy_arr(env);

    this->env.stdin_fd = dup(0);
    this->env.stdout_fd = dup(1);
    this->env.stderr_fd = dup(2);

    // char *PATH = strdup(get_env_var((char**)env, "PATH"));
    // char *rest = PATH;
    // char *dir;
    // while (1)
    // {
    //     dir = strtok_r(rest, ":", &rest);
    //     if (dir){
    //         DIR *dr = opendir(dir);
    //         struct dirent *en;
    //         if (dr) {
    //             while(en=readdir(dr)) {
    //                 string path = string(en->d_name);
    //                 if (path!="." && path!="..") {
                        
    //                     path_of[path] = (string(dir)+"/"+path).data();
    //                 }
    //             }
    //             closedir(dr);
    //         }
    //     }
    //   else
    //     break;
    // }
    // esh_free_str(&PATH);
    // for (unordered_map<string, const char*>::iterator it=path_of.begin(); it!=path_of.end(); ++it) {
    //     printf("%s: %s\n", (*it).first.data(), (*it).second);
    // }
}

Shell::~Shell() {
    if (var.is_a_tty) esh_print_str("exit\n", 1);
    esh_free_str_arr(&env.env);
} 

void Shell::reset_fd() {
    dup2(this->env.stdin_fd, 0);
    dup2(this->env.stdout_fd, 1);
    dup2(this->env.stderr_fd, 2);
}