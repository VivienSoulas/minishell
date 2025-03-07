#include "parsing.h"

char	**ft_split_input(char *input, t_split *split)
{
	if (ft_check_quotes(input) == 1)
		return (ft_free_split(split->tokens), NULL);
	while (split->i < split->len)
	{
		if (ft_double_operator(input, split->i) == 1)
		{
			
		}
	}
}

int	ft_initialise_split(t_split *split, char *input)
{
	split->i = 0;
	split->j = 0;
	split->k = 0;
	split->len = ft_strlen(input);
	split->tokens = malloc(sizeof(char *) * (split->len + 1));
	if (split->tokens == NULL)
		return (1);
	return (0);
}
