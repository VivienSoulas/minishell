/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vsoulas <vsoulas@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/19 12:34:39 by jdavtian          #+#    #+#             */
/*   Updated: 2025/04/18 12:34:52 by vsoulas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

void	pipe_manage(int is_not_last, int *last_pipe_read, int *fd)
{
	if (is_not_last)
	{
		if (*last_pipe_read != -1)
			close(*last_pipe_read);
		close(fd[1]);
		*last_pipe_read = fd[0];
	}
}

int	init_pipe(int *fd, int last_pipe_read)
{
	if (pipe(fd) != 0)
	{
		perror("pipe");
		if (last_pipe_read != -1)
			close(last_pipe_read);
		return (-1);
	}
	return (0);
}

static int	command_count(t_command **commands)
{
	int	res;

	res = 0;
	if (commands == NULL)
		return (res);
	while (commands[res])
	{
		res++;
	}
	return (res);
}

static void	cleanup_fd(int *fd, int last_read_pipe)
{
	if (fd[0])
		close(fd[0]);
	if (fd[1])
		close(fd[1]);
	if (last_read_pipe != -1)
		close(last_read_pipe);
}

int	exe_cmds(t_command **c, t_envp **list, int *exit, t_token **token)
{
	int	i;
	int	fd[2];
	int	last_pipe_read;
	int	n_cmds;

	i = 0;
	last_pipe_read = -1;
	n_cmds = command_count(c);
	while (i < n_cmds)
	{
		if ((i < n_cmds - 1) && init_pipe(fd, last_pipe_read) != 0)
			return (-1);
		if (input_fd(c[i], i, last_pipe_read) != 0)
			return (cleanup_fd(fd, last_pipe_read), -1);
		if (output_fd(c[i], fd, i < n_cmds - 1) != 0)
			return (cleanup_fd(fd, last_pipe_read), -1);
		if (exe_command(c[i], list, exit, token) == -1)
			return (cleanup_fd(fd, last_pipe_read), -1);
		pipe_manage(i < n_cmds - 1, &last_pipe_read, fd);
		i++;
	}
	if (last_pipe_read != -1)
		close(last_pipe_read);
	return (0);
}
