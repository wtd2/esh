#include "esh.h"
#include "shell.h"
#include "prompt.h"

#include <string.h>
#include <unistd.h>


/* 
    this is a temporary function needs enhancement
    may lead to memory leak
*/

int prompt_input(struct s_esh *shell, char **raw) {
    const int BUFFER_SIZE = 4096;
    
    (*raw) = malloc(BUFFER_SIZE);
    read(0, (*raw), BUFFER_SIZE - 1);
    char *c = strchr((*raw), '\n');
    if (c != NULL) *c = 0;
    if (strcmp((*raw), "exit") == 0) {
        return 1;
    }

    /* success. */
    return 0;

    /* exit. */
    return 1;

    /* failed. */
    return -1;
}