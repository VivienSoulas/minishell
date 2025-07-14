/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vsoulas <vsoulas@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/30 14:08:13 by vsoulas           #+#    #+#             */
/*   Updated: 2025/07/10 15:29:14 by vsoulas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

void	ft_name_found(t_envp *prev, t_envp **list)
{
	prev = *list;
	*list = (*list)->next;
	free(prev->name);
	free(prev->value);
	return (free(prev));
}

void	ft_name_found_export(t_export *prev, t_export **list)
{
	prev = *list;
	*list = (*list)->next;
	free(prev->name);
	if (prev->value)
		free(prev->value);
	return (free(prev));
}

void	unset_export(t_command *command, t_export **list)
{
	t_export	*current;
	t_export	*prev;
	int			i;

	i = 1;
	if (!command->args[i])
		return ;
	while (command->args[i])
	{
		if (!ft_strcmp((*list)->name, command->args[i]))
			return (ft_name_found_export(prev, list));
		current = *list;
		prev = current;
		while (current && ft_strcmp(current->name, command->args[i]))
		{
			prev = current;
			current = current->next;
		}
		if (current)
		{
			prev->next = current->next;
			free_export(current);
		}
		i++;
	}
}

void	ft_free_env(t_envp *current)
{
	free(current->name);
	free(current->value);
	free(current);
}

void	free_export(t_export *current)
{
	free(current->name);
	free(current->value);
	free(current);
}
