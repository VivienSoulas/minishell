#include "parsing.h"

void	ft_free_list(t_token **token)
{
	t_token	*current;
	t_token	*next;

	if (token == NULL || *token == NULL)
	{
		printf("alredy free\n");
		return ;
	}
	current = *token;
	while (current)
	{
		next = current->next;
		free(current);
		current = next;
	}
	*token = NULL;
	printf("Token list freed.\n");
}

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

void	ft_free(char **tokens, t_token **token)
{
	if (tokens != NULL)
		ft_free_split(tokens);
	if (token != NULL)
		ft_free_list(token);
}
