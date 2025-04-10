#include "parsing.h"

void	ft_free_list(t_token **token)
{
	t_token	*current;
	t_token	*next;

	if (token == NULL || *token == NULL)
		return ;
	current = *token;
	while (current)
	{
		next = current->next;
		free(current->input);
		free(current);
		current = next;
	}
	*token = NULL;
}

void	ft_free_envp_list(t_envp **envp)
{
	t_envp	*current;
	t_envp	*next;

	if (envp == NULL || *envp == NULL)
		return ;
	current = *envp;
	while (current)
	{
		next = current->next;
		free(current->name);
		free(current->value);
		free(current);
		current = next;
	}
	*envp = NULL;
}

void	ft_free_split(char **split)
{
	int	i;

	i = 0;
	if (split != NULL && *split != NULL)
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
