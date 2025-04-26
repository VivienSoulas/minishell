#include "parsing.h"

// initialise split struct
int	ft_initialise_split(t_split *split, char *input)
{
	split->i = 0;
	split->j = 0;
	split->k = 0;
	split->len = ft_strlen(input);
	split->tokens = malloc(sizeof(char *) * (split->len + 1));
	if (split->tokens == NULL)
		return (error(3, NULL), 1);
	split->error = 0;
	return (0);
}

// check that open quotes are closed
int	ft_check_quotes(char *input)
{
	bool	in_double_quotes;
	bool	in_single_quotes;
	int		i;

	i = 0;
	in_double_quotes = false;
	in_single_quotes = false;
	while (input[i])
	{
		if (input[i] == '"' && !in_single_quotes)
			in_double_quotes = !in_double_quotes;
		else if (input[i] == '\'' && !in_double_quotes)
			in_single_quotes = !in_single_quotes;
		i++;
	}
	if (in_double_quotes || in_single_quotes)
		return (1);
	return (0);
}

// check if char c is an operator or white space
int	ft_is_operator(char c)
{
	if (c == ' ' || c == '\t' || c == '<' || c == '>' || c == '|')
		return (1);
	return (0);
}

// check for double operator (aka << or >>)
int	ft_double_operator(char *input, int i)
{
	if (input[i] == '<' && input[i + 1] == '<')
		return (1);
	else if (input[i] == '>' && input[i + 1] == '>')
		return (1);
	else
		return (0);
}
