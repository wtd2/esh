#ifndef SHELL_H
#define SHELL_H

#include <stdlib.h>
#include <stdbool.h>
#include <stdint.h>
#include <unistd.h>
#include <string>
#include "exec.h"

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
        const char *builtinList[8] = {"cd", "setenv", "unsetenv", "resetenv", "env", "history", "exit", NULL};

    private:
        vector<Command*> parse(char* line);
        int execute(Command *cmd, bool* last_pipe, int* fd);

        int prompt_input(char* line);
        int prompt_make_str(char *prompt_str);

        bool is_builtin(char *cmd);
        void exec_builtin(char *cmd, char *pram[]);

        void showenv();
        void setenv(char *newenv);
        void unsetenv(char *name);
        void resetenv(const char *name, char *value);
        void change_path(char *path);
        void shell_exit();
};  

int get_env_var_no(char **env, const char *name);
char *get_env_var(char **env, const char *name);

#endif