/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdavtian <jdavtian@student.codam.nl>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/19 13:00:41 by jdavtian          #+#    #+#             */
/*   Updated: 2025/03/28 15:46:14 by jdavtian         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

static void	close_fds(t_command *command)
{
	if (command->input_fd > 0)
		close(command->input_fd);
	if (command->output_fd > 0)
		close(command->output_fd);
}

int	line_read(char *delimiter, int *here_pipe)
{
	char	*line;

	line = readline(">");
	if (!line)
		return (1);
	if (!ft_strcmp(line, delimiter))
	{
		free(line);
		return (1);
	}
	write(here_pipe[1], line, ft_strlen(line));
	write(here_pipe[1], "\n", 1);
	free (line);
	return (0);
}

void	readline_here(char *delimiter)
{
	int		here_pipe[2];

	if (init_pipe(here_pipe, -1) != 0)
		exit(EXIT_FAILURE);
	while (1)
	{
		if (line_read(delimiter, here_pipe) != 0)
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

static int	handle_redirection(t_command *command)
{
	if (command->is_heredoc)
		readline_here(command->heredoc_delimiter);
	else if (command->input_fd > 0)
	{
		if (dup2(command->input_fd, STDIN_FILENO) == -1)
		{
			close_fds(command);
			perror("dup2");
			return (1);
		}
		close(command->input_fd);
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

void	exe_child(t_command *command, char **envp)
{
	if (handle_redirection(command) != 0)
		exit(EXIT_FAILURE);
	execve(command->executable_path, command->args, envp);
	perror("execv failed");
	exit(EXIT_FAILURE);
}

static void	reset_fds(int i_stdin, int i_stdout)
{
	if (i_stdin != -1)
	{
		dup2(i_stdin, STDIN_FILENO);
		close(i_stdin);
	}
	if (i_stdout != -1)
	{
		dup2(i_stdout, STDOUT_FILENO);
		close(i_stdout);
	}
}

int		exe_buildin(t_command *command, t_envp **envp, int *exit)
{
	int	return_value;
	int	initial_stdin;
	int initial_stdout;

	initial_stdin = -1;
	initial_stdout = -1;
	if (command->is_heredoc || command->input_fd > 0)
		initial_stdin = dup(STDIN_FILENO);
	if (command->output_fd > 0)
		initial_stdout = dup(STDOUT_FILENO);
	if (handle_redirection(command) != 0)
		return (1);
	return_value = exec_buildin(command, envp, exit);
	reset_fds(initial_stdin, initial_stdout);
	close_fds(command);
	return (return_value);
}

int	exe_command(t_command *command, t_envp **list, int *exit)
{
	pid_t	pid;
	int		status;
	char	**envp;

	if (command->is_buildin)
		return (exe_buildin(command, list, exit));
	envp = list_to_array(list);
	if (!envp)
		return (-1);
	pid = fork();
	if (pid < 0)
	{
		close_fds(command);
		perror("fork");
		return (-1);
	}
	if (pid == 0)
		exe_child(command, envp);
	close_fds(command);
	if (waitpid(pid, &status, 0) == -1)
		return (-1);
	free_array(envp);
	if (WIFEXITED(status))
		return (WEXITSTATUS(status));
	return (0);
}
