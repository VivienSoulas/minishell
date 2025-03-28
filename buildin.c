#include "parsing.h"

void echo(t_command *command);

int	is_buildin(char *command)
{
	static char *buildins[] = {
		"pwd",
		"cd",
		"unset",
		"env",
		"echo"
	};
	int i;

	i = 0;
	while (i < 5)
	{
		if (ft_strcmp(command, buildins[i]) == 0)
			return (1);
		i++;
	}
	return (0);
}

int	exec_buildin(t_command *cmd, t_envp **envp)
{
	if (!ft_strcmp(cmd->args[0], "echo"))
	{
		echo(cmd);
	}
	if (!ft_strcmp(cmd->args[0], "env"))
		env(envp);
	if (!ft_strcmp(cmd->args[0], "pwd"))
		pwd(envp);
	return (0);
}

void	env(t_envp **env)
{
	t_envp *current;

	current = *env;
	while (current)
	{
		printf("%s=%s\n", current->name, current->value);
		current = current->next;
	}
}
void	pwd(t_envp **env)
{
	t_envp *current;

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

void echo(t_command *command)
{
	int	i;
	int	j;
	int	no_new_line;

	no_new_line = 0;
	i = 1;
	if (!command->args[i])
	{
		printf("\n");
		exit(EXIT_SUCCESS);
	}
	if (!ft_strcmp(command->args[i], "-n"))
	{
		no_new_line = 1;
		i++;
	}
	j = 0;
	while (command->args[i][j])
	{
		write(1, &command->args[i][j], 1);
		j++;
	}
	if (!no_new_line)
		write(1, "\n", 1);
	exit(EXIT_SUCCESS);
}
