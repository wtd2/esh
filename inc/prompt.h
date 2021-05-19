#ifndef PROMPT_H
#define PROMPT_H

void prompt_display(struct s_esh *shell);
int prompt_input(struct s_esh *shell, char **raw);

#endif