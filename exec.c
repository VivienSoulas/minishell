/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdavtian <jdavtian@student.codam.nl>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/19 12:34:39 by jdavtian          #+#    #+#             */
/*   Updated: 2025/07/18 12:26:55 by jdavtian         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

static int	wait_for_childs(int n_cmds, t_expansion *e)
{
	int	last_exit_status;
	int	i;
	int	status;

	last_exit_status = 0;
	i = -1;
	if (e->pids == NULL)
		return (e->exit_stat);
	while (++i < n_cmds)
	{
		signal(SIGINT, &child);
		if (e->pids[i] != -1)
		{
			if (waitpid(e->pids[i], &status, 0) == -1)
				return (free(e->pids),
					e->pids = NULL, perror("waitpid"), 1);
			close_fds(e->cmd[i]);
			if (WIFEXITED(status))
				last_exit_status = WEXITSTATUS(status);
		}
	}
	sig_hand(MAIN);
	free(e->pids);
	return (e->pids = NULL, e->exit_stat = last_exit_status);
}

void	clean_fds(t_exec *exec)
{
	if (exec->i < exec->n_cmds - 1)
		close(exec->pipe_fds[1]);
	if (exec->i < exec->n_cmds - 1)
		exec->last_pipe_read = exec->pipe_fds[0];
	else
		exec->last_pipe_read = -1;
}

static void	close_heredoc_fds(t_expansion *e, int n_cmds)
{
	int	i;

	i = 0;
	while (i < n_cmds)
	{
		if (e->cmd[i]->is_heredoc && e->cmd[i]->input_fd > 2)
		{
			close(e->cmd[i]->input_fd);
			e->cmd[i]->input_fd = -1;
		}
		i++;
	}
}

void	close_current_heredoc_fd(t_exec *exec, t_expansion *e)
{
	if (e->cmd[exec->i]->is_heredoc && e->cmd[exec->i]->input_fd > 2)
	{
		close(e->cmd[exec->i]->input_fd);
		e->cmd[exec->i]->input_fd = -1;
	}
}

int	exe_cmds(t_command **c, t_expansion *e, t_token **token)
{
	t_exec	exec;
	int		prev_pipe_read;

	prev_pipe_read = -1;
	exec.i = 0;
	exec.n_cmds = command_count(c);
	e->pids = malloc(sizeof(pid_t) * exec.n_cmds);
	if (!e->pids)
		return (error(3, NULL), 1);
	close_heredoc_fds(e, exec.n_cmds);
	exec.last_pipe_read = -1;
	while (exec.i < exec.n_cmds)
	{
		if (execution(&exec, e, token, c) == 1)
			return (1);
		if (prev_pipe_read != -1)
			close(prev_pipe_read);
		prev_pipe_read = exec.last_pipe_read;
		exec.i++;
	}
	if (exec.last_pipe_read != -1)
		close(exec.last_pipe_read);
	close_heredoc_fds(e, exec.n_cmds);
	return (wait_for_childs(exec.n_cmds, e));
}
