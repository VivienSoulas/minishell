/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdavtian <jdavtian@student.codam.nl>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/10 11:20:23 by jdavtian          #+#    #+#             */
/*   Updated: 2025/07/18 12:24:44 by jdavtian         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	pipe_init(t_exec *exec, t_expansion *e)
{
	if (exec->i < exec->n_cmds - 1)
		if (init_pipe(exec->pipe_fds) == -1)
			return (free(e->pids), e->pids = NULL, 1);
	return (0);
}

int	in_out_setup(t_exec *exec, t_expansion *e)
{
	t_command	**c;

	c = e->cmd;
	if ((input_fd(c[exec->i], exec->i, exec->last_pipe_read) != 0
			|| output_fd(c[exec->i], exec->pipe_fds,
				exec->i < exec->n_cmds - 1) != 0))
	{
		close_fds(c[exec->i]);
		if (exec->i < exec->n_cmds -1)
		{
			close(exec->pipe_fds[0]);
			close(exec->pipe_fds[1]);
		}
		e->pids[exec->i] = -1;
		return (1);
	}
	return (0);
}

int	exec_process(t_exec *exec, t_expansion *e)
{
	t_command	**c;

	c = e->cmd;
	e->pids[exec->i] = fork();
	if (e->pids[exec->i] == 0)
	{
		sig_hand(CHILD);
		if (exec->i < exec->n_cmds - 1)
			close(exec->pipe_fds[0]);
		if (c[exec->i]->is_buildin)
		{
			exec->i = exe_buildin(c[exec->i], e, e->token);
			ft_free_e(&e);
			exit(exec->i);
		}
		exe_child(c[exec->i], e);
	}
	else if (e->pids[exec->i] < 0)
		return (perror("fork"), free(e->pids), e->pids = NULL, 1);
	clean_fds(exec);
	close_current_heredoc_fd(exec, e);
	return (0);
}

int	execution(t_exec *exe, t_expansion *e, t_token **t, t_command **c)
{
	if (pipe_init(exe, e))
		return (clean_fds(exe), free(e->pids), e->pids = NULL, 1);
	if (in_out_setup(exe, e))
		return (clean_fds(exe), free(e->pids), e->pids = NULL, 1);
	if (exe->n_cmds == 1 && is_buildin(c[0]->args[0]))
		return (clean_fds(exe), free(e->pids), e->pids = NULL,
			exe_buildin(c[0], e, t));
	if (exec_process(exe, e))
		return (clean_fds(exe), free(e->pids), e->pids = NULL, 1);
	clean_fds(exe);
	close_current_heredoc_fd(exe, e);
	return (0);
}
