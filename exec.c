/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vsoulas <vsoulas@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/19 12:34:39 by jdavtian          #+#    #+#             */
/*   Updated: 2025/07/11 11:54:14 by vsoulas          ###   ########.fr       */
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
			return (sig_hand(MAIN), 1);
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
	t_exec	exec;

	exec.i = -1;
	exec.n_cmds = command_count(c);
	e->pids = malloc(sizeof(pid_t) * exec.n_cmds);
	if (!e->pids)
		return (error(3, NULL), 1);
	exec.last_pipe_read = -1;
	while (++exec.i < exec.n_cmds)
	{
		if (pipe_init(&exec, e))
			return (free(e->pids), e->pids = NULL, 1);
		if (in_out_setup(&exec, e))
			continue ;
		if (exec.n_cmds == 1 && is_buildin(c[0]->args[0]))
			return (free(e->pids), e->pids = NULL, exe_buildin(c[0], e, token));
		if (exec_process(&exec, e))
			return (free(e->pids), e->pids = NULL, 1);
		clean_fds(exec.i, exec.n_cmds, exec.pipe_fds, &exec.last_pipe_read);
	}
	if (exec.last_pipe_read != -1)
		close(exec.last_pipe_read);
	return (wait_for_childs(exec.n_cmds, e));
}
