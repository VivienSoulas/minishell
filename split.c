//#include "parsing.h"

/* =================================================================================== */
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include "parsing.h"

int	ft_handles_operator(t_split *split, char *input);
int	ft_handles_operator(t_split *split, char *input);

void	ft_free_split(char **split)
{
	int	i;

	i = 0;
	if (split != NULL)
	{
		while (split[i])
		{
			free(split[i]);
			i++;
		}
		free(split);
		split = NULL;
	}
}

size_t	ft_strlen(char *s)
{
	size_t	i;

	i = 0;
	while (s[i] != '\0')
		i++;
	return (i);
}

char	*ft_strdup(char *s)
{
	char	*str;
	int		total;
	int		i;

	i = 0;
	total = ft_strlen(s);
	str = (char *)malloc(total + 1);
	if (str == NULL)
		return (NULL);
	while (i < total)
	{
		str[i] = s[i];
		i++;
	}
	str[i] = '\0';
	return (str);
}
/* =================================================================================== */


char	**ft_split_input(char *input, t_split *split)
{
	if (ft_check_quotes(input) == 1)
		return (ft_free_split(split->tokens), NULL);
	while (split->i < split->len)
	{
		if (ft_double_operator(input, split->i) == 1)
		{
			if (ft_handles_double(split, input) == 1)
				return (ft_free_split(split->tokens), NULL);
		}
		else if (ft_is_operator(input[split->i]) == 1)
		{
			if (ft_handles_operator(split, input) == 1)
				return (ft_free_split(split->tokens), NULL);
		}
		else if (input[split->i] == '\'' || input[split->i] == '\"')
		{
			split->quote_type = input[split->i];
			while (split->i < split->len && input[split->i] != split->quote_type)
				split->current_token[split->k++] = input[split->i++];
			if (split->i < split->len)
				split->i++;
		}
		else
			split->current_token[split->k++] = input[split->i++];
		if (split->k != 0 && (ft_is_operator(input[split->i]) || input[split->i] == '\0'))
		{
			split->current_token[split->k] = '\0';
			split->tokens[split->j++] = ft_strdup(split->current_token);
			if (split->tokens[split->j - 1] == NULL)
				return (ft_free_split(split->tokens), NULL);
			split->k = 0;
		}
	}
	split->tokens[split->j] = NULL;
	return (split->tokens);
}

// handles double operators like << or >>
int	ft_handles_double(t_split *split, char *input)
{
	if (split->k != 0)
	{
		split->current_token[split->k] = '\0';
		split->tokens[split->j] = ft_strdup(split->current_token);
		if (split->tokens[split->j] == NULL)
			return (1);
		split->k = 0;
		split->j++;
	}
	split->current_token[0] = input[split->i];
	split->current_token[1] = input[split->i + 1];
	split->current_token[2] = '\0';
	split->tokens[split->j] = ft_strdup(split->current_token);
	if (split->tokens[split->j] == NULL)
		return (1);
	split->j++;
	split->i += 2;
	return (0);
}

// handle single operators
int	ft_handles_operator(t_split *split, char *input)
{
	if (split->k != 0)
	{
		split->current_token[split->k] = '\0';
		split->tokens[split->j] = ft_strdup(split->current_token);
		if (split->tokens[split->j] == NULL)
			return (1);
		split->k = 0;
		split->j++;
	}
	if (input[split->i] != ' ' || input[split->i] != '\t')
	{
		split->current_token[0] = input[split->i];
		split->current_token[1] = '\0';
		split->tokens[split->j] = ft_strdup(split->current_token);
		if (split->tokens[split->j] == NULL)
			return (1);
		split->j++;
	}
	split->i++;
	return (0);
}


// do not remove quotes single dont expand '$ARG' (do for "$ARG" and $ARG)
int	main(void)
{
	char		*test_input;
	char		**tokens;
	int			i;
	t_split		*split;

	i = 0;
	test_input = "<infile grep	'$US<ER' \"$USER\"|wc  -l>outfile <<append		>>append echo -n \"hello world	this|\"";
	split = malloc(sizeof(t_split));
	if (split == NULL)
		return (1);
	if (ft_initialise_split(split, test_input) == 1)
	{
		//free(split);
		return (1);
	}
	tokens = ft_split_input(test_input, split);
	if (tokens == NULL)
	{
		printf("Error: Unmatched quotes in input\n");
		//free(split);
		return (1);
	}
	while (tokens[i])
	{
		printf("Token[%d]: %s\n", i, tokens[i]);
		//free(tokens[i]);
		i++;
	}
	//free(tokens);
	//free(split);
	return (0);
}
