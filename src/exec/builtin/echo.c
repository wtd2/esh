#include "esh.h"

#include <unistd.h>

static void	ft_putstr_echo(char *s)
{
	int i;

	i = 0;
	while (s[i] != '\0')
	{
		write(1, &s[i], 1);
		i++;
	}
}