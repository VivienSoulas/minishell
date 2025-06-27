/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vsoulas <vsoulas@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/19 12:34:39 by jdavtian          #+#    #+#             */
/*   Updated: 2025/06/05 16:42:35 by vsoulas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

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

static int	wait_for_childs(int n_cmds, t_expansion *e)
{
	int	last_exit_status;
	int	i;
	int	status;

	last_exit_status = 0;
	i = -1;
	while (++i < n_cmds)
	{
		signal(SIGINT, &child);
		if (waitpid(e->pids[i], &status, 0) == -1)
		{
			free(e->pids);
			e->pids = NULL;
			return (sig_hand(MAIN)/* , perror("waitpid") */, 1);
		}
		if (WIFEXITED(status))
		{
			last_exit_status = WEXITSTATUS(status);
		}
	}
	sig_hand(MAIN);
	free(e->pids);
	e->pids = NULL;
	e->exit_stat = last_exit_status;
	return (e->exit_stat);
}

static void	clean_fds(int i, int n_cmds, int *pipe_fd, int *last_pipe_read)
{
	if (i < n_cmds - 1)
		close(pipe_fd[1]);
	if (*last_pipe_read != -1)
		close(*last_pipe_read);
	if (i < n_cmds - 1)
		*last_pipe_read = pipe_fd[0];
}

int	exe_cmds(t_command **c, t_expansion *e, t_token **token)
{
	int		i;
	int		n_cmds;
	int		pipe_fd[2];
	int		last_pipe_read;

	i = -1;
	n_cmds = command_count(c);
	if (n_cmds == 1 && !ft_strcmp(c[0]->args[0], "exit"))
		return (exe_buildin(c[0], e, token));
	e->pids = malloc(sizeof(pid_t) * n_cmds);
	if (!e->pids)
		return (error(3, NULL), 1);
	last_pipe_read = -1;
	while (++i < n_cmds)
	{
		if (i < n_cmds - 1)
			if (pipe(pipe_fd) == -1)
				return (perror("pipe"), free(e->pids), e->pids = NULL, 1);
		if ((input_fd(c[i], i, last_pipe_read) != 0
			|| output_fd(c[i], pipe_fd, i < n_cmds - 1) != 0))
			// return (free(e->pids), 1);
			{
				if ( i < n_cmds -1)
				{
					close(pipe_fd[0]);
					close(pipe_fd[1]);
				}
				e->pids[i] = -1;
				continue ;
			}
		e->pids[i] = fork();
		if (e->pids[i] == 0)
		{
			sig_hand(CHILD);
			if (i < n_cmds - 1)
				close(pipe_fd[0]);
			if (c[i]->is_buildin)
			{
				// if (!ft_strcmp(c[i]->args[0], "exit"))
				// {
				// 	ft_free_e(&e);
				// 	exit(0);
				// }
				i = exe_buildin(c[i], e, token);
				ft_free_e(&e);
				exit(i);
			}
			exe_child(c[i], e);
		}
		else if (e->pids[i] < 0)
			return (perror("fork"), free(e->pids), e->pids = NULL, 1);
		clean_fds(i, n_cmds, pipe_fd, &last_pipe_read);
	}
	if (last_pipe_read != -1)
		close(last_pipe_read);
	return (wait_for_childs(n_cmds, e));
}
