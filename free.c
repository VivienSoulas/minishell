/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vsoulas <vsoulas@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/10 12:01:06 by vsoulas           #+#    #+#             */
/*   Updated: 2025/06/05 16:41:34 by vsoulas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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

void	free_array(char **array)
{
	int	i;

	if (!array || !*array)
		return ;
	i = 0;
	while (array[i])
	{
		free(array[i]);
		i++;
	}
	free(array);
}

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
	free(*e);
	*e = NULL;
}
