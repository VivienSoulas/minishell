/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vsoulas <vsoulas@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/19 13:00:41 by jdavtian          #+#    #+#             */
/*   Updated: 2025/04/18 15:03:38 by vsoulas          ###   ########.fr       */
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
		ft_variable_expansion(&temp, e->env, e->exit);
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

// if delimiter is inside quote signs then no expansion
void	readline_here(char *delimiter, t_expansion *e)
{
	int		here_pipe[2];
	int		expand;

	expand = 1;
	if (delimiter[0] == 34 || delimiter[0] == 39)
	{
		if (ft_heredoc_delimiter(&expand, delimiter) == 1)
			exit(EXIT_FAILURE);
	}
	if (init_pipe(here_pipe, -1) != 0)
		exit(EXIT_FAILURE);
	while (1)
	{
		if (line_read(delimiter, here_pipe, expand, e) != 0)
			break ;
	}
	close(here_pipe[1]);
	if (dup2(here_pipe[0], STDIN_FILENO) == -1)
	{
		close(here_pipe[0]);
		perror("dup2");
		exit(EXIT_FAILURE);
	}
	close(here_pipe[0]);
}

int	handle_redirection(t_command *command, t_envp **env, int *exit)
{
	t_expansion	*e;

	e = malloc(sizeof(t_expansion));
	if (e == NULL)
		return (error(3, NULL), 1);
	ft_initialise_expansion(e, env, exit);
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
	return (free(e), 0);
}

int	exe_buildin(t_command *c, t_envp **envp, int *exit, t_token **t)
{
	int	return_value;
	int	initial_stdin;
	int	initial_stdout;
printf("C.%i\n", *exit);
	initial_stdin = -1;
	initial_stdout = -1;
	if (c->is_heredoc || c->input_fd > 0)
		initial_stdin = dup(STDIN_FILENO);
	if (c->output_fd > 0)
		initial_stdout = dup(STDOUT_FILENO);
	if (handle_redirection(c, envp, exit) != 0)
		return (1);
	return_value = exec_buildin(c, envp, exit, t);
	reset_fds(initial_stdin, initial_stdout);
	close_fds(c);
	return (return_value);
}

int	exe_command(t_command *c, t_envp **list, int *exit, t_token **t)
{
	pid_t	pid;
	int		status;
	char	**envp;
printf("B.%i\n", *exit);
	if (c->is_buildin)
		return (exe_buildin(c, list, exit, t));
	envp = list_to_array(list);
	if (!envp)
		return (-1);
	pid = fork();
	if (pid < 0)
	{
		close_fds(c);
		perror("fork");
		return (-1);
	}
	if (pid == 0)
		exe_child(c, envp, list, exit);
	close_fds(c);
	if (waitpid(pid, &status, 0) == -1)
		return (-1);
	free_array(envp);
	if (WIFEXITED(status))
		return (WEXITSTATUS(status));
	return (*exit);
}
