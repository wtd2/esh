#ifndef PROMPT_H
#define PROMPT_H

void get_prompt_str(struct s_esh *shell, char* prompt_str);
int prompt_input(struct s_esh *shell, char **raw);

#endif