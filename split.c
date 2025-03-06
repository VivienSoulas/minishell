// #include "parsing.h"
#include <stdio.h>
#include <stdlib.h>

void	ft_fill(char *input, char **tokens)
{
	int	len;
	int	i;

	len = 0;
	i = 0;
	while (input[i])
	{
		if (ft_is_token(input[i]) != 0)
		{
			in_word == 1;
			if (ft_is_token(input[i + 1]) == 2 || ft_is_token(input[i + 1]) == 3)
				i++;
			else if (ft_is_token(input[i]) == 10 || ft_is_token(input[i]) == -1)
			{
				while (ft_is_token(input[i]) != 10 || ft_is_token(input[i]) == -1)
					i++;
				if (ft_is_token(input[i]) == 10)
					i++;
			}
		// 	else if (ft_is_token(input[i]) == -1)
		// 	{
		// 		while (ft_is_token(input[i]) == -1)
		// 			i++;
		// 	}
		}
		else if (in_word == 0)
		{
			words++;
			in_word = 1;
		}
		i++;
	}
	return (words);
}

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

char	**split_input(char *input)
{
	int		words;
	char	**tokens;

	words = word_count(input);
	tokens = malloc(sizeof(char *) * words + 1);
	if (tokens == NULL)
		return (NULL);
	ft_fill(input, tokens);
	
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
			else if (ft_is_token(input[i]) == 10 || ft_is_token(input[i]) == -1)
			{
				while (ft_is_token(input[i]) != 10 || ft_is_token(input[i]) == -1)
					i++;
				if (ft_is_token(input[i]) == 10)
					i++;
			}
		// 	else if (ft_is_token(input[i]) == -1)
		// 	{
		// 		while (ft_is_token(input[i]) == -1)
		// 			i++;
		// 	}
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


#include <stdio.h>

// Declare the word_count function
int word_count(char *input);

int main()
{
    char *test_input = "<infile grep '$USER' \"$USER\"|wc -l>outfile";
    int result = word_count(test_input);
    printf("Word count: %d\n", result); // Expected output: 8

    return 0;
}