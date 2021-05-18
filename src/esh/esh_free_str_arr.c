#include "esh.h"

#include <string.h>
#include <stdlib.h>

void esh_free_str_arr(char ***arr) {
    size_t i = 0;
    while ((*arr)[i] != NULL) {
        free((*arr)[i++]);
    }
    free(*arr);
    *arr = NULL;
}