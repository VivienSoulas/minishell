/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vsoulas <vsoulas@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/19 13:00:41 by jdavtian          #+#    #+#             */
/*   Updated: 2025/07/11 11:22:53 by vsoulas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

int	handle_redirection(t_command *command, t_expansion *e)
{
	if (command->is_heredoc)
		readline_here(command->heredoc_delimiter, e);
	else if (command->input_fd >= 0)
	{
		if (ft_fd_0(command) == 1)
			return (1);
	}
	if (command->output_fd > 0)
	{
		if (dup2(command->output_fd, STDOUT_FILENO) == -1)
		{
			close_fds(command);
			perror("dup2");
			return (1);
		}
		close(command->output_fd);
	}
	return (0);
}

int	exe_buildin(t_command *c, t_expansion *e, t_token **t)
{
	int	return_value;

	if (c->is_heredoc || c->input_fd >= 0)
		e->initial_stdin = dup(STDIN_FILENO);
	if (c->output_fd > 0)
		e->initial_stdout = dup(STDOUT_FILENO);
	if (handle_redirection(c, e) != 0)
		return (1);
	return_value = exec_buildin(c, e, t);
	reset_fds(e->initial_stdin, e->initial_stdout);
	return (return_value);
}

int	exe_command(t_command *c, t_expansion *e, t_token **t)
{
	pid_t	pid;
	int		stat;

	if (c->is_buildin && !(c->input_fd >= 0 || c->output_fd > 1))
		return (exe_buildin(c, e, t));
	pid = fork();
	if (pid == 0)
	{
		if (c->is_buildin)
		{
			stat = exe_buildin(c, e, t);
			ft_free_e(&e);
			exit(stat);
		}
		exe_child(c, e);
	}
	else if (pid < 0)
		return (close_fds(c), perror("fork"), -1);
	if (waitpid(pid, &stat, 0) == -1)
		return (close_fds(c), -1);
	if (WIFEXITED(stat))
		return (close_fds(c), e->exit_stat = WEXITSTATUS(stat));
	return (close_fds(c), e->exit_stat);
}
