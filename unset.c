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

void	unset(t_command *command, t_envp **list)
{
	t_envp	*current;
	t_envp	*prev;
	int		i;

	i = 1;
	if (!command->args[i])
		return ;
	while (command->args[i])
	{
		if (!ft_strcmp((*list)->name, command->args[i]))
			return (ft_name_found(prev, list));
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
			ft_free_env(current);
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
