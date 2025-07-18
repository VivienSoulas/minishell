/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_redirection.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdavtian <jdavtian@student.codam.nl>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/18 14:51:59 by jdavtian          #+#    #+#             */
/*   Updated: 2025/07/17 12:31:32 by jdavtian         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

static int	grab_word(t_token **token, char **dest)
{
	*token = (*token)->next;
	if (*token == NULL)
		return (error(1, NULL), -1);
	if (*dest && !ft_strncmp(*dest, "herefile", 8))
		unlink(*dest);
	if (*dest)
		free(*dest);
	*dest = ft_strdup((*token)->input);
	if (!*dest)
		return (error(3, NULL), -1);
	return (0);
}

int	ft_out_append(t_command *command, t_token **token)
{
	if ((*token)->type == APPEND)
		command->is_append = 1;
	else
		command->is_append = 0;
	if (grab_word(token, &command->output_file) == -1)
		return (-1);
	return (0);
}

int	handle_here(t_command *command, t_token **token, t_expansion *e)
{
	command->is_heredoc = 1;
	if (grab_word(token, &command->heredoc_delimiter) == -1)
		return (1);
	readline_here(command, e);
	return (0);
}

int	init_redirection(t_token **token, t_command *command, t_expansion *e)
{
	while (*token && ((*token)->type > 0 && (*token)->type < 6))
	{
		if ((*token)->type == PIPE)
			command->is_pipe = 1;
		else if ((*token)->type == IN)
		{
			if (grab_word(token, &command->input_file) == -1
				|| open_input_file(command) == -1)
				return (-1);
		}
		else if ((*token)->type == HEREDOC && handle_here(command, token, e))
			return (-1);
		else if ((*token)->type == OUT || (*token)->type == APPEND)
			if (ft_out_append(command, token) == -1
				|| open_output_file(command) == -1)
				return (-1);
		*token = (*token)->next;
	}
	return (0);
}
