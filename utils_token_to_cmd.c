/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_to_command.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdavtian <jdavtian@student.codam.nl>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/18 14:56:14 by jdavtian          #+#    #+#             */
/*   Updated: 2025/07/17 12:05:11 by jdavtian         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

int	count_commands(t_token **tokens)
{
	int		n;
	t_token	*current;

	n = 0;
	current = *tokens;
	while (current != NULL)
	{
		if (current->type == CMD && ft_strlen(current->input) != 0)
			n++;
		current = current->next;
	}
	return (n);
}

int	count_args(t_token *token)
{
	int	n;

	n = 0;
	if (token && token->type == CMD)
	{
		n++;
		token = token->next;
	}
	while (token && token->type == ARG)
	{
		n++;
		token = token->next;
	}
	return (n);
}

void	ft_free_partial_args(t_command *cmd, int up_to_index)
{
	int	i;

	i = 0;
	while (i < up_to_index)
	{
		free(cmd->args[i]);
		i++;
	}
}
