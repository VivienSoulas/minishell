/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_parsing.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vsoulas <vsoulas@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/18 12:28:03 by vsoulas           #+#    #+#             */
/*   Updated: 2025/04/18 12:28:04 by vsoulas          ###   ########.fr       */
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
