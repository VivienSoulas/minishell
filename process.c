/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vsoulas <vsoulas@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/19 13:00:41 by jdavtian          #+#    #+#             */
/*   Updated: 2025/03/28 14:38:26 by vsoulas          ###   ########.fr       */
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
	if (!line || !ft_strncmp(line, delimiter, ft_strlen(line)))
	{
		if (line)
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

void	exe_child(t_command *command, char **envp, t_envp **env)
{
	if (command->is_heredoc)
		readline_here(command->heredoc_delimiter);
	else if (command->input_fd > 0)
	{
		if (dup2(command->input_fd, STDIN_FILENO) == -1)
		{
			close_fds(command);
			perror("dup2");
			exit(EXIT_FAILURE);
		}
		close(command->input_fd);
	}
	if (command->output_fd > 0)
	{
		if (dup2(command->output_fd, STDOUT_FILENO) == -1)
		{
			close(command->output_fd);
			perror("dup2");
			exit(EXIT_FAILURE);
		}
		close(command->output_fd);
	}
	if (command->is_buildin)
		exec_buildin(command, env);
	execve(command->executable_path, command->args, envp);
	perror("execv failed");
	exit(EXIT_FAILURE);
}

int	exe_command(t_command *command, t_envp **list)
{
	pid_t	pid;
	int		status;
	char	**envp;

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
		exe_child(command, envp, list);
	close_fds(command);
	if (waitpid(pid, &status, 0) == -1)
		return (-1);
	free_array(envp);
	if (WIFEXITED(status))
		return (WEXITSTATUS(status));
	return (0);
}
