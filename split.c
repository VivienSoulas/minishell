#include "parsing.h"

char	**ft_split_input(char *input)
{
	int		i;
	int		j;
	int		k;
	int		len;
	char	**tokens;


	i = 0;
	j = 0;
	k = 0;
	len = ft_strlen(input);
	tokens = malloc(sizeof(char *) * (len + 1));
	if (tokens == NULL)
		return (NULL);
	if (ft_check_quotes(input) == 1)
		return(ft_free_split(tokens), NULL);
	while (i < len)
	{
		if (ft_double_operator(input, i) == 1)
			ft_handles_double(k, tokens, i);
		i++;
	}
}

int	ft_handles_double(int k, char **token, int i)
{
	char	*current_token[256];

	if (k != 0)
	{
		current_token[k] == '\0';
		
	}
}