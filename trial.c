//// #include "parsing.h"
#include <stdio.h>
#include <stdlib.h>

/* ======================================================================= */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

// check that every open single or double quote is closed
int	ft_check_quotes(char *in)
{
	int	single;
	int	duble;

	single = 0;
	duble = 0;
	while (*in)
	{
		if (*in == 39)
			single++;
		if (*in == 34)
			duble++;
		in++;
	}
	if (single % 2 != 0 || duble % 2 != 0)
		return (1);
	return (0);
}

// check for single tokens and white spaces
int	ft_is_token(char c)
{
	if (c == ' ' || c == '<' || c == '>' || c == '|' || c == '\t')
		return (1);
	return (0);
}

// check for multiple tokens (<< and >>)
int	is_multi_char_token(char *input, int i)
{
	if ((input[i] == '<' && input[i + 1] == '<')
		|| (input[i] == '>' && input[i + 1] == '>'))
		return (1);
	return (0);
}

char	**split_input(char *input)
{
	int		i;
	int		j;
	int		k;
	int		len;
	char	**tokens;
	char	current_token[256];
	char	quote_type;

	i = 0;
	j = 0;
	k = 0;
	len = strlen(input);
	tokens = malloc(sizeof(char *) * (len + 1));
	if (tokens == NULL)
		return (NULL);
	if (ft_check_quotes(input) == 1)
		return (NULL);
	while (i < len)
	{
		if (is_multi_char_token(input, i))
		{
			if (k > 0)
			{
				current_token[k] = '\0';
				tokens[j++] = strdup(current_token);
				k = 0;
			}
			current_token[0] = input[i];
			current_token[1] = input[i + 1];
			current_token[2] = '\0';
			tokens[j++] = strdup(current_token);
			i += 2;
		}
		else if (ft_is_token(input[i]))
		{
			if (k > 0)
			{
				current_token[k] = '\0';
				tokens[j++] = strdup(current_token);
				k = 0;
			}
			if (input[i] != ' ')
			{
				current_token[0] = input[i];
				current_token[1] = '\0';
				tokens[j++] = strdup(current_token);
			}
			i++;
		}
		else if (input[i] == '\'' || input[i] == '\"')
		{
			quote_type = input[i++];
			current_token[k++] = quote_type;
			while (i < len && input[i] != quote_type)
				current_token[k++] = input[i++];
			if (i < len)
				current_token[k++] = input[i++];
		}
		else
		{
			current_token[k++] = input[i++];
		}
	}
	if (k > 0)
	{
		current_token[k] = '\0';
		tokens[j++] = strdup(current_token);
	}
	tokens[j] = NULL;
	return (tokens);
}

int	main(void)
{
	char	*test_input;
	char	**tokens;
	int		i;

	i = 0;
	test_input = "<infile grep '$USER' \"$USER\"|wc -l>outfile <<append >>append";
	tokens = split_input(test_input);
	if (tokens == NULL)
	{
		printf("Error: Unmatched quotes in input\n");
		return (1);
	}
	while (tokens[i])
	{
		printf("Token[%d]: %s\n", i, tokens[i]);
		free(tokens[i]);
		i++;
	}
	free(tokens);
	return (0);
}
/* ======================================================================= */