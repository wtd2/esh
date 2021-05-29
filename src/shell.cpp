#include "esh.h"
#include "shell.h"

#include <dirent.h>
#include <string.h>

#include <readline/readline.h>
#include <readline/history.h>

vector<string> path_of;

char* completion_generator(const char* text, int state) {
    if (state>100) return NULL;
    static vector<string> matches;
    static size_t match_index;
    if (state==0) {
        matches.clear();
        match_index=0;

        string textstr = string(text);
        for (auto path: path_of) {
            if (path.size() >= textstr.size() && path.compare(0, textstr.size(), textstr)==0) {
                matches.push_back(path);
            }
        }
    }
    
    if (match_index >= matches.size()) {
        return nullptr;
    } else {
        return strdup(matches[match_index++].c_str());
    }
}

char** completer (const char* text, int start, int end) {
    if (end==0 || start>0) return nullptr;
    return rl_completion_matches(text, (rl_compentry_func_t*)completion_generator);
}

Shell::Shell(const char *env[]) {
    this->var.exit = 0;
    this->var.is_a_tty = isatty(0);
    this->env.env = esh_cpy_arr(env);

    this->env.stdin_fd = dup(0);
    this->env.stdout_fd = dup(1);
    this->env.stderr_fd = dup(2);

    char *PATH = strdup(get_env_var((char**)env, "PATH"));
    char *rest = PATH;
    char *dir;
    while (1)
    {
        dir = strtok_r(rest, ":", &rest);
        if (dir){
            DIR *dr = opendir(dir);
            struct dirent *en;
            if (dr) {
                while(en=readdir(dr)) {
                    string path = string(en->d_name);
                    if (path!=string(".") && path!=string(".."))
                        path_of.push_back(path);
                }
                closedir(dr);
            }
        }
      else
        break;
    }
    
    esh_free_str(&PATH);
    rl_attempted_completion_function = (rl_completion_func_t*)completer;
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