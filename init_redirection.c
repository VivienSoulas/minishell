/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_redirection.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vsoulas <vsoulas@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/18 14:51:59 by jdavtian          #+#    #+#             */
/*   Updated: 2025/05/29 13:53:49 by vsoulas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

static int	grab_word(t_token **token, char **dest)
{
	*token = (*token)->next;
	if (*dest)
		free(*dest);
	*dest = ft_strdup((*token)->input);
	if (!*dest)
		return (error(3, NULL), -1);
	return (0);
}

int	init_redirection(t_token **token, t_command *command)
{
	while (*token && ((*token)->type > 0 && (*token)->type < 6))
	{
		if ((*token)->type == PIPE)
			command->is_pipe = 1;
		else if ((*token)->type == IN)
		{
			if (grab_word(token, &command->input_file) == -1)
				return (-1);
		}
		else if ((*token)->type == HEREDOC)
		{
			command->is_heredoc = 1;
			if (grab_word(token, &command->heredoc_delimiter) == -1)
				return (-1);
		}
		else if ((*token)->type == OUT || (*token)->type == APPEND)
		{
			if ((*token)->type == APPEND)
				command->is_append = 1;
			if (grab_word(token, &command->output_file) == -1)
				return (-1);
		}
		*token = (*token)->next;
	}
	return (0);
}
