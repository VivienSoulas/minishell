/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vsoulas <vsoulas@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/30 14:08:13 by vsoulas           #+#    #+#             */
/*   Updated: 2025/05/30 14:08:14 by vsoulas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

void	unset(t_command *command, t_envp **list)
{
	t_envp	*current;
	t_envp	*prev;

	if (!command->args[1])
		return ;
	if (!ft_strcmp((*list)->name, command->args[1]))
	{
		prev = *list;
		*list = (*list)->next;
		free(prev->name);
		free(prev->value);
		return (free(prev));
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
		prev->next = current->next;
		ft_free_env(current);
	}
}

void	ft_free_env(t_envp *current)
{
	free(current->name);
	free(current->value);
	free(current);
}
