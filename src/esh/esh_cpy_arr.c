#include "esh.h"

#include <string.h>
#include <stdlib.h>

char** esh_cpy_arr(const char *const *arr) {
    size_t len = 0;
    while(arr[len] != NULL) len++;
    char **ret = (char**)malloc(sizeof(char*) * (len + 1));
    if (ret != NULL) {
        size_t i = 0;
        while (arr[i] != NULL) {
            ret[i] = strdup(arr[i]);
            i++;
        }
        ret[i] = NULL;
    }
    return ret;
}