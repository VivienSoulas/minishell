#include "parsing.h"

int	is_buildin(char *command)
{
	static char	*buildins[] = {
		"pwd",
		"cd",
		"unset",
		"env",
		"echo",
		"exit"
	};
	int			i;

	i = 0;
	while (i < 6)
	{
		if (ft_strcmp(command, buildins[i]) == 0)
			return (1);
		i++;
	}
	return (0);
}

int	exec_buildin(t_command *cmd, t_envp **envp, int *exit)
{
	if (!ft_strcmp(cmd->args[0], "echo"))
	{
		echo(cmd/* , envp */);
	}
	if (!ft_strcmp(cmd->args[0], "env"))
		env(envp);
	if (!ft_strcmp(cmd->args[0], "pwd"))
		pwd(envp);
	if (!ft_strcmp(cmd->args[0], "exit"))
		return (*exit = 1);
	else if (!ft_strcmp(cmd->args[0], "unset"))
	{
		unset(cmd, envp);
	}
	return (0);
}

void	env(t_envp **env)
{
	t_envp	*current;

	current = *env;
	while (current)
	{
		printf("%s=%s\n", current->name, current->value);
		current = current->next;
	}
}

void	pwd(t_envp **env)
{
	t_envp	*current;

	current = *env;
	while (current)
	{
		if (ft_strncmp(current->name, "PWD", 4) == 0)
		{
			printf("%s\n", current->value);
			break ;
		}
		current = current->next;
	}
}

void	echo(t_command *command/* , t_envp **envp */)
{
	int	i;
	int	j;
	int	no_new_line;

	no_new_line = 0;
	i = 1;
	if (!command->args[i]/*  || ft_is_variable(command->args[1], envp) == 0 */)
	{
		printf("\n");
		return ;
	}
	if (!ft_strcmp(command->args[i], "-n"))
	{
		no_new_line = 1;
		i++;
	}
	while (command->args[i])
	{
		j = 0;
		while (command->args[i][j])
		{
			write(1, &command->args[i][j], 1);
			j++;
		}
		write(1, " ", 1);
		i++;
	}
	if (!no_new_line)
		write(1, "\n", 1);
	return ;
}

/* int	ft_is_variable(char *command, t_envp **envp)
{
	t_envp	*current;

	current = *envp;
	while (current)
	{
		if (ft_strncmp(current->name, command, ft_strlen(command)) == 0 )
			return (1);
		current = current->next;
	}
	return (0);
} */