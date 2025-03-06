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
	if (c == 39 || c == 34)
		return (10);
	return (0);
}

int word_count(char *input)
{
	int	in_word;
	int	words;
	int	i;

	in_word = 0;
	words = 0;
	i = 0;
	while (input[i])
	{
		if (ft_is_token(input[i]) != 0 && in_word == 0)
		{
			words++;
			in_word == 1;
			if (ft_is_token(input[i + 1]) == 2 || ft_is_token(input[i + 1]) == 3)
				i++;
			else if (ft_is_token(input[i]) == 10)
			{
				while (ft_is_token(input[i]) == 10)
					i++;
			}
			else if (ft_is_token(input[i]) == -1)
			{
				while (ft_is_token(input[i]) == -1)
					i++;
			}
		}
		else if (ft_is_token(input[i]) == 0 && in_word == 1)
			in_word = 0;
		else if (in_word == 0)
		{
			words++;
			in_word = 1;
		}
		i++;
	}
	return (words);
}
