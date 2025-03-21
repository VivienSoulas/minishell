#include "parsing.h"

// takes allocated fd
int	create_pipe(int *fd)
{
	if (pipe(fd) != 0)
	{
		perror("Pipe failed:");
		return (-1);
	}
	return (0);
}

void	readline_here(char *delimiter)
{
	char	*line;
	int		here_pipe[2];

	if (create_pipe(here_pipe) != 0)
		exit(EXIT_FAILURE);
	while (1)
	{
		line = readline(">");
		if (!line || !ft_strncmp(delimiter, line, ft_strlen(delimiter)))
		{
			free(line);
			break ;
		}
		write(here_pipe[1], line, ft_strlen(line));
		write(here_pipe[1], "\n", 1);
		free (line);
	}
	close(here_pipe[1]);
	if (dup2(here_pipe[0], STDIN_FILENO) == -1)
	{
		perror("dup2");
		exit(EXIT_FAILURE);
	}
	close(here_pipe[0]);
}

void	exec_process(t_command *command)
{
	if (command->is_heredoc)
		readline_here(command->heredoc_delimiter);
	else if (command->input_fd > 0)
	{
		if (dup2(command->input_fd, STDIN_FILENO) == -1)
		{
			perror("dup2");
			exit(EXIT_FAILURE);
		}
	}
	if (command->output_fd > 0)
	{
		if (dup2(command->output_fd, STDOUT_FILENO) == -1)
		{
			perror("dup2");
			exit(EXIT_FAILURE);
		}
	}
	execv(command->executable_path, command->args);
	perror("execv failed");
	exit(EXIT_FAILURE);
}

int	exec_command(t_command *command)
{
	pid_t	pid;
	int		status;

	pid = fork();
	if (pid < 0)
	{
		perror("fork");
		return (-1);
	}
	if (pid == 0)
		exec_process(command);
	else
	{
		waitpid(pid, &status, 0);
		if (WIFEXITED(status))
			return (WEXITSTATUS(status));
	}
	return (-1);
}

int	open_input_file(t_command *command)
{
	command->input_fd = open(command->input_file, O_RDONLY);
	if (command->input_fd == -1)
	{
		perror("open");
		return (-1);
	}
	return (0);
}

int	open_output_file(t_command *command)
{
	if (command->is_append)
		command->output_fd
			= open(command->output_file, O_WRONLY | O_CREAT | O_APPEND, 0644);
	else
		command->output_fd
			= open(command->output_file, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (command->output_fd == -1)
	{
		perror("open");
		return (-1);
	}
	return (0);
}

int	init_pipe(int *fd, int last_pipe_read)
{
	if (create_pipe(fd) != 0)
	{
		if (last_pipe_read != -1)
			close(last_pipe_read);
		return (-1);
	}
	return (0);
}

int	input_redirection(t_command *command, int i, int last_pipe_read)
{
	if (i > 0 && !command->input_file)
		command->input_fd = last_pipe_read;
	else if (command->input_file)
	{
		if (open_input_file(command) != 0)
			return (-1);
	}
	else
		command->input_fd = -1;
	return (0);
}

int	output_redirection(t_command *command, int *fd, int is_not_last)
{
	if (is_not_last && !command->output_file)
		command->output_fd = fd[1];
	else if (command->output_file)
	{
		if (open_output_file(command))
			return (-1);
	}
	else
		command->output_fd = -1;
	return (0);
}

void	pipe_manage(int is_not_last, int *last_pipe_read, int *fd)
{
	if (is_not_last)
	{
		if (*last_pipe_read != -1)
			close(*last_pipe_read);
		close(fd[1]);
		*last_pipe_read = fd[0];
	}
}

int	command_count(t_command **commands)
{
	int	n_commands;

	n_commands = 0;
	while (commands[n_commands])
	{
		n_commands++;
	}
	return (n_commands);
}

int	exec_list_command(t_command **commands)
{
	int	i;
	int	fd[2];
	int	last_pipe_read;
	int	n_commands;

	i = 0;
	last_pipe_read = -1;
	n_commands = command_count(commands);
	while (i < n_commands)
	{
		if (i < n_commands - 1 && init_pipe(fd, last_pipe_read) != 0)
			return (-1);
		if (input_redirection(commands[i], i, last_pipe_read) != 0)
			return (-1);
		if (output_redirection(commands[i], fd, i < n_commands - 1) != 0)
			return (-1);
		if (exec_command(commands[i]) == -1)
			return (-1);
		pipe_manage(i < n_commands - 1, &last_pipe_read, fd);
		i++;
	}
	if (last_pipe_read != -1)
		close(last_pipe_read);
	return (0);
}
