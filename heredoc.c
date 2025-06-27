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

void	ft_heredoc(char *deli, t_expansion *e, int *here_pipe, int *expand)
{
	while (1)
	{
		if (line_read(deli, here_pipe, *expand, e) != 0)
			break ;
	}
	ft_free_e(&e);
	close(here_pipe[1]);
	exit(EXIT_SUCCESS);
}

void	readline_cleanup(pid_t pid, int *here_pipe, t_expansion *e)
{
	int	status;

	waitpid(pid, &status, 0);
	signal(SIGINT, &heredoc);
	if (WEXITSTATUS(status) != 0)
	{
		ft_free_e(&e);
		close(here_pipe[0]);
		exit(130);
	}
	if (dup2(here_pipe[0], STDIN_FILENO) == -1)
	{
		ft_free_e(&e);
		close(here_pipe[0]);
		perror("dup2");
		exit(EXIT_FAILURE);
	}
	close(here_pipe[0]);
}

void	ft_pid_0(int *here_pipe, char *delim, t_expansion *e, int *expand)
{
	sig_hand(HEREDOC);
	close(here_pipe[0]);
	ft_heredoc(delim, e, here_pipe, expand);
}

void	readline_here(char *delim, t_expansion *e)
{
	int		here_pipe[2];
	pid_t	pid;
	int		expand;

	expand = 1;
	if (delim[0] == 34 || delim[0] == 39)
	{
		if (ft_heredoc_delimiter(&expand, &delim) == 1)
			exit(EXIT_FAILURE);
	}
	if (init_pipe(here_pipe) != 0)
		exit(EXIT_FAILURE);
	pid = fork();
	if (pid == -1)
	{
		perror("fork");
		close(here_pipe[0]);
		close(here_pipe[1]);
		exit(EXIT_FAILURE);
	}
	if (pid == 0)
		ft_pid_0(here_pipe, delim, e, &expand);
	close(here_pipe[1]);
	readline_cleanup(pid, here_pipe, e);
}
