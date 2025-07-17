/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmds_free.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdavtian <jdavtian@student.codam.nl>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/30 14:07:53 by vsoulas           #+#    #+#             */
/*   Updated: 2025/07/17 12:36:19 by jdavtian         ###   ########.fr       */
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
		free(command->input_file);
	if (command->output_file)
		free(command->output_file);
	if (command->heredoc_delimiter)
		free(command->heredoc_delimiter);
	if (command->executable_path)
		free(command->executable_path);
}

void	command_cleanup(t_command **commands)
{
	int			i;
	int			j;

	i = -1;
	if (!commands || !*commands)
		return ;
	while (commands[++i])
	{
		free_strings(commands[i]);
		if (commands[i]->args)
		{
			j = -1;
			while (commands[i]->args[++j])
			{
				free(commands[i]->args[j]);
				commands[i]->args[j] = NULL;
			}
			free(commands[i]->args);
			commands[i]->args = NULL;
		}
		free(commands[i]);
		commands[i] = NULL;
	}
	free(commands);
	commands = NULL;
}
