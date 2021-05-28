#ifndef PROMPT_H
#define PROMPT_H

#include <readline/readline.h>
#include <readline/history.h>

void prompt_display(struct s_esh *shell);
int prompt_input(struct s_esh *shell, char **raw);

#endif