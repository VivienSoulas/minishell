/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmds_free.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdavtian <jdavtian@student.codam.nl>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/30 14:07:53 by vsoulas           #+#    #+#             */
/*   Updated: 2025/07/18 14:26:43 by jdavtian         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

void	free_strings(t_command *command)
{
	if (command->input_fd > 2)
		close(command->input_fd);
	if (command->input_file && !ft_strncmp(command->input_file, "herefile", 8))
		unlink(command->input_file);
	if (command->input_file)
	{
		free(command->input_file);
		command->input_file = NULL;
	}
	if (command->output_file)
	{
		free(command->output_file);
		command->output_file = NULL;
	}
	if (command->heredoc_delimiter)
	{
		free(command->heredoc_delimiter);
		command->heredoc_delimiter = NULL;
	}
	if (command->executable_path)
	{
		free(command->executable_path);
		command->executable_path = NULL;
	}
}

static int	count_cmds(t_command ***commands)
{
	int	count;

	count = 0;
	while ((*commands)[count])
		count++;
	return (count);
}

static void	free_set_null(void **data)
{
	if (data && *data)
	{
		free(*data);
		*data = NULL;
	}
}

void	command_cleanup(t_command ***commands)
{
	int			i;
	int			j;
	int			count;

	if (!commands || !*commands)
		return ;
	count = count_cmds(commands);
	i = -1;
	while (++i < count)
	{
		if ((*commands)[i])
			free_strings((*commands)[i]);
		if ((*commands)[i] && (*commands)[i]->args)
		{
			j = -1;
			while ((*commands)[i]->args[++j])
				free_set_null((void **)&((*commands)[i]->args[j]));
			free_set_null((void **)&((*commands)[i]->args));
		}
		free((*commands)[i]);
		(*commands)[i] = NULL;
	}
	free(*commands);
	*commands = NULL;
}
