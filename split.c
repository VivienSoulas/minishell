#include "parsing.h"

int	ft_is_token(char c)
{
	if (c == '|')
		return (1);
	if (c == '<')
		return (2);
	if (c == '>')
		return (3);
	if (c == ' ' || c == '\t')
		return (-1);
	return (0);
}

char	**split_input(char *input)
{
	int	in_word;
	int	words;
	int	i;

	in_word = 0;
	words = 0;
	i = 0;
	while (input[i])
	{

	}
}