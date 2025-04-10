#include "parsing.h"

void	error(int i, char *str)
{
	if (i == 1)
		printf("Invalid Input\n");
	else if (i == 2)
		printf("`%s' not a valid identifier\n", str);
	else if (i == 3)
		printf("Malloc error, exiting minishell\n");
}
