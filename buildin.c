#include "parsing.h"

int	is_buildin(char *command)
{
	static char	*buildins[] = {
		"pwd",
		"cd",
		"unset",
		"env",
		"exit",
		"echo"
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
	if (!ft_strcmp(cmd->args[0], "pwd"))
		pwd(envp);
	else if (!ft_strcmp(cmd->args[0], "unset"))
		unset(cmd, envp);
	else if (!ft_strcmp(cmd->args[0], "env"))
		env(envp);
	else if (!ft_strcmp(cmd->args[0], "echo"))
		return (2);
	else if (!ft_strcmp(cmd->args[0], "exit"))
		return (*exit = 1);
	return (0);
}

void	env(t_envp **env)
{
	t_envp	*current;

	current = *env;
	while (current)
	{
		if (current->value != NULL && ft_strncmp(current->value, "", 1) != 0)
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

int	echo(t_token **token, t_envp **env, int *exit_stat)
{
	int		no_new_line;
	t_token	*current;

	no_new_line = 0;
	current = (*token)->next;
	if (current && !ft_strcmp(current->input, "-n"))
	{
		no_new_line = 1;
		current = current->next;
	}
	while (current)
	{
		if (ft_strchr(current->input, '$') != 0)
		{
		if (ft_variable_expansion(current, env, exit_stat) == 1)
			return (1);
		}
			write(1, current->input, ft_strlen(current->input));
			if (current->next != NULL)
				write(1, " ", 1);
		current = current->next;
	}
	if (!no_new_line)
		write(1, "\n", 1);
	return (0);
}
