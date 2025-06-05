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
		free((void *)temp.input);
		free(line);
		return (0);
	}
	write(here_pipe[1], line, ft_strlen(line));
	write(here_pipe[1], "\n", 1);
	if (line)
		free(line);
	return (0);
}

void	ft_heredoc(char *delimiter, t_expansion *e, int *here_pipe, int expand)
{
	while (1)
	{
		if (line_read(delimiter, here_pipe, expand, e) != 0)
			break ;
	}
	close(here_pipe[1]);
	exit(EXIT_SUCCESS);
}

void	readline_cleanup(pid_t pid, int *here_pipe)
{
	int	status;

	waitpid(pid, &status, 0);
	if (WEXITSTATUS(status) != 0)
	{
		close(here_pipe[0]);
		exit(EXIT_FAILURE);
	}
	if (dup2(here_pipe[0], STDIN_FILENO) == -1)
	{
		close(here_pipe[0]);
		perror("dup2");
		exit(EXIT_FAILURE);
	}
	close(here_pipe[0]);
}

static int	init_pipe(int *fd)
{
	if (pipe(fd) != 0)
	{
		perror("pipe");
		return (-1);
	}
	return (0);
}

void	readline_here(char *delimiter, t_expansion *e)
{
	int		here_pipe[2];
	int		expand;
	pid_t	pid;

	expand = 1;
	if (delimiter[0] == 34 || delimiter[0] == 39)
	{
		if (ft_heredoc_delimiter(&expand, &delimiter) == 1)
			exit(EXIT_FAILURE);
	}
	if (init_pipe(here_pipe) != 0)
		exit(EXIT_FAILURE);
	signal(SIGINT, &heredoc);
	pid = fork();
	if (pid == -1)
	{
		perror("fork");
		close(here_pipe[0]);
		close(here_pipe[1]);
		exit(EXIT_FAILURE);
	}
	if (pid == 0)
	{
		close(here_pipe[0]);
		sig_hand(HEREDOC);
		ft_heredoc(delimiter, e, here_pipe, expand);
	}
	close(here_pipe[1]);
	readline_cleanup(pid, here_pipe);
}
