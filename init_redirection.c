/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_redirection.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdavtian <jdavtian@student.codam.nl>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/18 14:51:59 by jdavtian          #+#    #+#             */
/*   Updated: 2025/06/03 15:10:03 by jdavtian         ###   ########.fr       */
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
			if (command->output_file)
			{
				int temp_fd;
				if (command->is_append)
					temp_fd = open(command->output_file, O_WRONLY | O_CREAT | O_APPEND, 0644);
				else
					temp_fd = open(command->output_file, O_WRONLY | O_CREAT | O_TRUNC, 0644);
				if (temp_fd != -1)
					close(temp_fd);
				else
				{
					return (-1);
				}
			}
			if ((*token)->type == APPEND)
				command->is_append = 1;
			else
				command->is_append = 0;
			if (grab_word(token, &command->output_file) == -1)
				return (-1);
		}
		*token = (*token)->next;
	}
	return (0);
}
