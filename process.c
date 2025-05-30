/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vsoulas <vsoulas@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/19 13:00:41 by jdavtian          #+#    #+#             */
/*   Updated: 2025/05/30 16:23:09 by vsoulas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

int	line_read(char *delim, int *here_pipe, int expand, t_expansion *e)
{
	char		*line;
	t_token		temp;

	line = readline(">");
	if (!line)
		return (1);
	if (!ft_strcmp(line, delim))
		return (free(line), 1);
	if (expand)
	{
		temp.input = ft_strdup(line);
		if (temp.input == NULL)
			error(3, NULL);
		ft_variable_expansion(&temp, e);
		write(here_pipe[1], temp.input, ft_strlen(temp.input));
		write(here_pipe[1], "\n", 1);
		return (0);
	}
	write(here_pipe[1], line, ft_strlen(line));
	write(here_pipe[1], "\n", 1);
	if (line)
		free(line);
	return (0);
}

static void heredoc_sigint_handler(int sig)
{
    (void)sig;
    g_signal_caught = 1;
    write(1, "\n", 1);
}

// if delimiter is inside quote signs then no expansion
void	readline_here(char *delimiter, t_expansion *e)
{
	int		here_pipe[2];
	int		expand;
void	(*here_doc_handler)(int);

	expand = 1;
	if (delimiter[0] == 34 || delimiter[0] == 39)
	{
		if (ft_heredoc_delimiter(&expand, &delimiter) == 1)
			exit(EXIT_FAILURE);
	}
	if (init_pipe(here_pipe, -1) != 0)
		exit(EXIT_FAILURE);

		
g_signal_caught = 0; // Reset before heredoc
here_doc_handler = signal(SIGINT, heredoc_sigint_handler); // Set heredoc handler

while (g_signal_caught == 0)
{
	if (line_read(delimiter, here_pipe, expand, e) != 0)
		break ;
}
signal(SIGINT, here_doc_handler);


	if (dup2(here_pipe[0], STDIN_FILENO) == -1)
	{
		close(here_pipe[0]);
		perror("dup2");
		exit(EXIT_FAILURE);
	}
	close(here_pipe[0]);
}

int	handle_redirection(t_command *command, t_expansion *e)
{
	if (command->is_heredoc)
		readline_here(command->heredoc_delimiter, e);
	else if (command->input_fd > 0)
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
	int	initial_stdin;
	int	initial_stdout;

	initial_stdin = -1;
	initial_stdout = -1;
	if (c->is_heredoc || c->input_fd > 0)
		initial_stdin = dup(STDIN_FILENO);
	if (c->output_fd > 0)
		initial_stdout = dup(STDOUT_FILENO);
	if (handle_redirection(c, e) != 0)
		return (1);
	return_value = exec_buildin(c, e, t);
	reset_fds(initial_stdin, initial_stdout);
	close_fds(c);
	return (return_value);
}

int	exe_command(t_command *c, t_expansion *e, t_token **t)
{
	pid_t	pid;
	int		status;

	if (c->is_buildin && !(c->input_fd > 0 || c->output_fd > 1))
		return (exe_buildin(c, e, t));
	pid = fork();
	if (pid < 0)
		return (close_fds(c), perror("fork"), -1);
	if (pid == 0)
	{
		if (c->is_buildin)
		{
			status = exe_buildin(c, e, t);
			ft_free_e(&e);
			exit(status);
		}
		exe_child(c, e);
	}
	close_fds(c);
	if (waitpid(pid, &status, 0) == -1)
		return (-1);
	if (WIFEXITED(status))
		return (e->exit_stat = WEXITSTATUS(status));
	return (e->exit_stat);
}
