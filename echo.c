#include "parsing.h"

int	echo_print(char *current, t_expansion *e, t_command *cmd, int fd)
{
	t_token	token;
	int		i;

	i = 1;
	if (!ft_strcmp(current, "-n"))
		current = cmd->args[++i];
	while (current)
	{
		token.input = ft_strdup(current);
		if (token.input == NULL)
			return (1);
		if (ft_variable_expansion(&token, e) == 1)
			return (free(token.input), 1);
		write(fd, token.input, ft_strlen(token.input));
		current = cmd->args[++i];
		if (current)
			write(fd, " ", 1);
		free(token.input);
		token.input = NULL;
	}
	return (0);
}

int	echo(t_command *cmd, t_expansion *e, int fd)
{
	int		no_new_line;
	char	*current;
	int		i;

	i = 1;
	no_new_line = 0;
	current = cmd->args[i];
	if (current && !ft_strcmp(current, "-n"))
	{
		no_new_line = 1;
	}
	if (echo_print(current, e, cmd, fd) == 1)
		return (1);
	if (!no_new_line)
		write(fd, "\n", 1);
	return (0);
}
