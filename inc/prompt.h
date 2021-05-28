#ifndef PROMPT_H
#define PROMPT_H

#include <readline/readline.h>
#include <readline/history.h>

int prompt_input(struct s_esh *shell, char *line);

#endif