#include "parsing.h"

void	close_fds(t_command *command)
{
	if (command->input_fd > 0)
		close(command->input_fd);
	if (command->output_fd > 0)
		close(command->output_fd);
}

void	exe_child(t_command *c, char **envp, t_expansion *e)
{
	if (handle_redirection(c, e) != 0)
		exit(e->exit_stat = 1);
	execve(c->executable_path, c->args, envp);
	perror("execv failed");
	e->exit_stat = 127;
	exit(e->exit_stat);
}

void	reset_fds(int i_stdin, int i_stdout)
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

int	ft_heredoc_delimiter(int *expand, char *delimiter)
{
	char	*temp;
	int		len;

	*expand = 0;
	temp = ft_strdup(delimiter + 1);
	if (!temp)
	{
		printf("malloc error");
		return (1);
	}
	len = ft_strlen(temp);
	temp[len - 1] = '\0';
	delimiter = temp;
	return (0);
}

int	ft_fd_0(t_command *command)
{
	if (dup2(command->input_fd, STDIN_FILENO) == -1)
	{
		close_fds(command);
		perror("dup2");
		return (1);
	}
	close(command->input_fd);
	return (0);
}
