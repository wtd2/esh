#ifndef SHELL_H
#define SHELL_H

#include <stdlib.h>
#include <stdbool.h>
#include <stdint.h>
#include <unistd.h>
#include <unordered_map>

#include <readline/readline.h>
#include <readline/history.h>

using namespace std;

struct s_var {
    bool exit;
    bool is_a_tty;
    uint8_t return_value;
};

struct s_env {
    int stdin_fd;
    int stdout_fd;
    int stderr_fd;
    char **env;
    // char *oldpwd;
};

class Shell {
    public:
        Shell(const char *env[]);
        ~Shell();

        struct s_var var;
        struct s_env env;

        void loop_shell();
        void reset_fd();
        
    private:
        unordered_map<string, const char*> path_of;

        int prompt_input(char* line);
        int prompt_make_str(char *prompt_str);
};  

int get_env_var_no(char **env, const char *name);
char *get_env_var(char **env, const char *name);

#endif