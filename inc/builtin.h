#include <stdbool.h>
#include <unistd.h>

bool is_builtin(char *cmd);
void exec_builtin(struct s_esh *shell, char *cmd, char *pram[]);

void change_path(struct s_esh *shell, char *path);

void showenv(struct s_esh *shell);
void setenv(struct s_esh *shell, char *newenv);
void unsetenv(struct s_esh *shell, char *oldenv);
void resetenv(struct s_esh *shell, char *name, char *value);

void esh_kill(pid_t pid)