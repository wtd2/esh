#include "esh.h"

#include <string.h>
#include <stdlib.h>

void esh_free_str(char **str) {
	if (str == (char**)NULL || *str == (char*)NULL)
		return;
    free(*str);
    *str = NULL;
}