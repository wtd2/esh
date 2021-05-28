#include "esh.h"
#include "shell.h"

#include <string.h>
#include <unistd.h>
#include <stdio.h>

void exit(struct s_esh *shell)
{
    shell->var.exit=1;
}