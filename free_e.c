/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_e.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vsoulas <vsoulas@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/10 15:55:42 by vsoulas           #+#    #+#             */
/*   Updated: 2025/07/10 15:55:43 by vsoulas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

void	ft_free_e(t_expansion **e)
{
	if (!e && !(*e))
		return ;
	if ((*e)->env)
	{
		ft_free_envp_list(&(*e)->env);
		free((*e)->env);
		(*e)->env = NULL;
	}
	if ((*e)->envp)
	{
		free_array((*e)->envp);
		(*e)->envp = NULL;
	}
	if ((*e)->export)
	{
		ft_free_export_list(&(*e)->export);
		free((*e)->export);
		(*e)->export = NULL;
	}
	ft_free_e_2(e);
	free(*e);
	*e = NULL;
}

void	ft_free_e_2(t_expansion **e)
{
	if ((*e)->cmd)
	{
		command_cleanup((*e)->cmd);
		(*e)->cmd = NULL;
	}
	if ((*e)->token)
	{
		ft_free_list((*e)->token);
		(*e)->token = NULL;
	}
	if ((*e)->pids)
	{
		free((*e)->pids);
		(*e)->pids = NULL;
	}
	if ((*e)->initial_stdin != -1)
		close((*e)->initial_stdin);
	if ((*e)->initial_stdout != -1)
		close((*e)->initial_stdout);
}

void	ft_free_export_list(t_export **envp)
{
	t_export	*current;
	t_export	*next;

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
