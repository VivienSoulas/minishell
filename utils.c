#include "parsing.h"

int	ft_count_args(char **tokens)
{
	int	i;

	i = 0;
	while (tokens[i])
		i++;
	return (i);
}
