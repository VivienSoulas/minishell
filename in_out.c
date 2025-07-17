/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   in_out.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdavtian <jdavtian@student.codam.nl>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/19 12:41:10 by jdavtian          #+#    #+#             */
/*   Updated: 2025/07/17 11:39:52 by jdavtian         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

int	open_input_file(t_command *command)
{
	if (command->input_fd > 2)
		close(command->input_fd);
	command->input_fd = open(command->input_file, O_RDONLY);
	if (command->input_fd == -1)
	{
		perror(command->input_file);
		return (-1);
	}
	return (0);
}

int	open_output_file(t_command *command)
{
	if (command->output_fd > 2)
		close(command->output_fd);
	if (command->is_append)
		command->output_fd
			= open(command->output_file, O_WRONLY | O_CREAT | O_APPEND, 0644);
	else
		command->output_fd
			= open(command->output_file, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (command->output_fd == -1)
	{
		perror("open");
		return (-1);
	}
	return (0);
}

int	input_fd(t_command *command, int i, int last_pipe_read)
{
	if (i > 0 && !command->input_file)
		command->input_fd = last_pipe_read;
	else if (command->input_file)
	{
		if (open_input_file(command) != 0)
			return (-1);
	}
	else
		command->input_fd = -1;
	return (0);
}

int	output_fd(t_command *command, int *fd, int is_not_last)
{
	if (is_not_last && !command->output_file)
		command->output_fd = fd[1];
	else if (command->output_file)
	{
		if (open_output_file(command) != 0)
			return (-1);
	}
	else
		command->output_fd = -1;
	return (0);
}
