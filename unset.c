#include "parsing.h"

void	unset(t_command *command, t_envp **list)
{
	t_envp	*current;
	t_envp	*prev;

	if (!ft_strcmp((*list)->name, command->args[1]))
	{
		prev = *list;
		*list = (*list)->next;
		free(prev->name);
		free(prev->value);
		free(prev);
		return ;
	}
	current = *list;
	prev = current;
	while (current && ft_strcmp(current->name, command->args[1]))
	{
		prev = current;
		current = current->next;
	}
	if (current)
	{
		ft_free_env(current);
		prev->next = current->next;
	}
}

void	ft_free_env(t_envp *current)
{
	free(current->name);
	free(current->value);
	free(current);
}
