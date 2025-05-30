/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_parsing.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vsoulas <vsoulas@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/18 12:28:03 by vsoulas           #+#    #+#             */
/*   Updated: 2025/05/30 12:21:57 by vsoulas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

int	ft_pipe_check(t_token **token)
{
	int		pipes;
	int		cmds;
	t_token	*current;

	pipes = 0;
	cmds = 0;
	current = *token;
	while (current)
	{
		if (current->type == PIPE)
			pipes++;
		else if (current->type == CMD)
			cmds++;
		current = current->next;
	}
	if (cmds - pipes == 0)
		return (1);
	return (0);
}

int	ft_check_tokens(t_token **token, t_expansion *e)
{
	t_token	*node;

	node = *token;
	if (node == NULL)
		return (e->exit_stat = 127, 1);
	if (ft_pipe_check(token) == 1)
		return (e->exit_stat = 127, 1);
	while (node && node->next)
	{
		if (node->type == FORBIDDEN)
			return (e->exit_stat = 127, 1);
		if (((node->type >= 1 && node->type <= 5)
				&& (node->next->type >= 1 && node->next->type <= 5))
			|| (node->type == 1 && node->next->type == 1))
			return (1);
		node = node->next;
	}
	if (node->next == NULL && (node->type >= 1 && node->type <= 5))
		return (e->exit_stat = 127, 1);
	return (0);
}
