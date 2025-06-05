/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdavtian <jdavtian@student.codam.nl>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/19 12:34:39 by jdavtian          #+#    #+#             */
/*   Updated: 2025/06/05 13:18:16 by jdavtian         ###   ########.fr       */
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

static int	wait_for_childs(int n_cmds, pid_t *pids, t_expansion *e)
{
	int	last_exit_status;
	int	i;
	int	status;

	last_exit_status = 0;
	i = -1;
	while (++i < n_cmds)
	{
		signal(SIGINT, &child);
		if (waitpid(pids[i], &status, 0) == -1)
			return (sig_hand(MAIN), perror("waitpid"), free(pids), 1);
		if (WIFEXITED(status))
			last_exit_status = WEXITSTATUS(status);
	}
	sig_hand(MAIN);
	free(pids);
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
	pid_t	*pids;
	int		pipe_fd[2];
	int		last_pipe_read;

	i = -1;
	n_cmds = command_count(c);

	if (n_cmds == 1 && !ft_strcmp(c[0]->args[0], "exit"))
		return (exe_buildin(c[0], e, token));
	pids = malloc(sizeof(pid_t) * n_cmds);
	if (!pids)
		return (error(3, NULL), 1);
	last_pipe_read = -1;
	while (++i < n_cmds)
	{
		if (i < n_cmds - 1)
			if (pipe(pipe_fd) == -1)
				return (perror("pipe"), free(pids), 1);
		if (input_fd(c[i], i, last_pipe_read) != 0
			|| output_fd(c[i], pipe_fd, i < n_cmds - 1) != 0)
			return (free(pids), 1);
		pids[i] = fork();
		if (pids[i] == 0)
		{
			sig_hand(CHILD);
			if (i < n_cmds - 1)
				close(pipe_fd[0]);
			if (c[i]->is_buildin)
			{
				if (!ft_strcmp(c[i]->args[0], "exit"))
				{
					ft_free_e(&e);
					exit(0);
				}
				i = exe_buildin(c[i], e, token);
				ft_free_e(&e);
				exit(i);
			}
			exe_child(c[i], e);
		}
		else if (pids[i] < 0)
			return (perror("fork"), free(pids), 1);
		clean_fds(i, n_cmds, pipe_fd, &last_pipe_read);
	}
	if (last_pipe_read != -1)
		close(last_pipe_read);
	return (wait_for_childs(n_cmds, pids, e));
}
