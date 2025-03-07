#include "parsing.h"

char	**ft_split_input(char *input, t_split *split)
{
	if (ft_check_quotes(input) == 1)
		return (ft_free_split(split->tokens), split->tokens = NULL, NULL);
	while (split->i < split->len && split->error == 0)
	{
		if (ft_double_operator(input, split->i) == 1)
			ft_handles_double(split, input);
		else if (ft_is_operator(input[split->i]) == 1)
			ft_handles_operator(split, input);
		else if (input[split->i] == '\'' || input[split->i] == '\"')
			ft_handles_quotes(input, split);
		else
			split->current_token[split->k++] = input[split->i++];
		if (split->k != 0 && (ft_is_operator(input[split->i])
				|| input[split->i] == '\0'))
			ft_handles_string(input, split);
	}
	if (split->error != 0)
		return (ft_free_split(split->tokens), split->tokens = NULL, NULL);
	split->tokens[split->j] = NULL;
	return (split->tokens);
}

// handles double operators like << or >>
void	ft_handles_double(t_split *split, char *input)
{
	if (split->k != 0)
	{
		split->current_token[split->k] = '\0';
		split->tokens[split->j] = ft_strdup(split->current_token);
		if (split->tokens[split->j] == NULL)
		{
			split->error = 1;
			return ;
		}
		split->k = 0;
		split->j++;
	}
	split->current_token[0] = input[split->i];
	split->current_token[1] = input[split->i + 1];
	split->current_token[2] = '\0';
	split->tokens[split->j] = ft_strdup(split->current_token);
	if (split->tokens[split->j] == NULL)
	{
		split->error = 1;
		return ;
	}
	split->j++;
	split->i += 2;
}

// handle single operators
void	ft_handles_operator(t_split *split, char *input)
{
	if (split->k != 0)
	{
		split->current_token[split->k] = '\0';
		split->tokens[split->j] = ft_strdup(split->current_token);
		if (split->tokens[split->j] == NULL)
		{
			split->error = 1;
			return ;
		}
		split->k = 0;
		split->j++;
	}
	if (input[split->i] != ' ' && input[split->i] != '\t')
	{
		split->current_token[0] = input[split->i];
		split->current_token[1] = '\0';
		split->tokens[split->j] = ft_strdup(split->current_token);
		if (split->tokens[split->j] == NULL)
		{
			split->error = 1;
			return ;
		}
		split->j++;
	}
	split->i++;
}

// handles quotes
// do not remove quotes
// single dont expand '$ARG' ("$ARG" and $ARG expand !!)
void	ft_handles_quotes(char *input, t_split *split)
{
	split->quote_type = input[split->i];
	split->current_token[split->k++] = input[split->i++];
	while (split->i < split->len && input[split->i] != split->quote_type)
		split->current_token[split->k++] = input[split->i++];
	if (split->i < split->len)
		split->current_token[split->k++] = input[split->i++];
}

// handles strings
void	ft_handles_string(char *input, t_split *split)
{
	(void)input;
	split->current_token[split->k] = '\0';
	split->tokens[split->j++] = ft_strdup(split->current_token);
	if (split->tokens[split->j - 1] == NULL)
	{
		split->error = 1;
		return ;
	}
	split->k = 0;
}

/* ===========================================================*/
// #include <unistd.h>
// #include <stdio.h>
// #include <stdlib.h>
// // #include "parsing.h"

// void	ft_free_split(char **split)
// {
// 	int	i;

// 	i = 0;
// 	if (split != NULL)
// 	{
// 		while (split[i])
// 		{
// 			free(split[i]);
// 			i++;
// 		}
// 		free(split);
// 		split = NULL;
// 	}
// }

// size_t	ft_strlen(char *s)
// {
// 	size_t	i;

// 	i = 0;
// 	while (s[i] != '\0')
// 		i++;
// 	return (i);
// }

// char	*ft_strdup(char *s)
// {
// 	char	*str;
// 	int		total;
// 	int		i;

// 	i = 0;
// 	total = ft_strlen(s);
// 	str = (char *)malloc(total + 1);
// 	if (str == NULL) 
// 		return (NULL); 
// 	while (i < total) 
// 	{
// 		str[i] = s[i];
// 		i++;
// 	}
// 	str[i] = '\0';
// 	return (str);
// }

// int	main(void)
// {
// 	char		*test_input;
// 	char		**tokens;
// 	int			i;
// 	t_split		*split;

// 	i = 0;
// 	test_input = "$ARG="1234" <infile grep	'$US<ER' \"$USER\"|wc  -l>outfile <<append		>>append echo -n \"hello world	this\" expdand $ARG dont_expand '$ARG' expand \"$ARG\";
// 	split = malloc(sizeof(t_split));
// 	if (split == NULL)
// 		return (1);
// 	if (ft_initialise_split(split, test_input) == 1)
// 	{
// 		free(split);
// 		return (1);
// 	}
// 	tokens = ft_split_input(test_input, split);
// 	if (tokens == NULL)
// 	{
// 		printf("Error: Unmatched quotes in input\n");
// 		free(split);
// 		return (1);
// 	}
// 	while (tokens[i])
// 	{
// 		printf("Token[%d]: %s\n", i, tokens[i]);
// 		free(tokens[i]);
// 		i++;
// 	}
// 	free(tokens);
// 	free(split);
// 	return (0);
// }
/* ===========================================================*/
