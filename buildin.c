/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   buildin.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vsoulas <vsoulas@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/10 12:00:40 by vsoulas           #+#    #+#             */
/*   Updated: 2025/07/10 15:55:29 by vsoulas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

int	is_buildin(char *command)
{
	static char	*buildins[] = {
		"pwd",
		"cd",
		"unset",
		"env",
		"exit",
		"echo",
		"/bin/echo",
		"export"
	};
	int			i;

	i = 0;
	while (i < 8)
	{
		if (ft_strcmp(command, buildins[i]) == 0)
			return (1);
		i++;
	}
	return (0);
}

int	exec_buildin(t_command *cmd, t_expansion *e, t_token **t)
{
	int	fd;

	fd = STDOUT_FILENO;
	if (!ft_strcmp(cmd->args[0], "pwd"))
	{
		if (cmd->args[1])
			return (printf("pwd: too many arguments\n"), e->exit_stat = 0);
		return (pwd(&e->env), e->exit_stat = 0);
	}
	else if (!ft_strcmp(cmd->args[0], "unset"))
		return (unset(cmd, &e->env), e->exit_stat = 0);
	else if (!ft_strcmp(cmd->args[0], "env"))
		return (env(cmd, e), e->exit_stat);
	else if (!ft_strcmp(cmd->args[0], "echo")
		|| !ft_strcmp(cmd->args[0], "/bin/echo"))
		return (echo(cmd, e, fd), e->exit_stat = 0);
	else if (!ft_strcmp(cmd->args[0], "exit"))
		return (ft_exit(e, cmd));
	else if (!ft_strcmp(cmd->args[0], "cd"))
		return (cd(cmd, e), e->exit_stat = 1);
	else if (!ft_strcmp(cmd->args[0], "export"))
		return (ft_export_check(t, e, fd), e->exit_stat = 0);
	return (e->exit);
}

int	env(t_command *cmd, t_expansion *e)
{
	t_envp	*current;

	if (cmd->args[1])
		return (printf("env: too many arguments\n"), e->exit_stat = 0);
	current = e->env;
	while (current)
	{
		printf("%s", current->name);
		if (current->value)
			printf("=%s", current->value);
		printf("\n");
		current = current->next;
	}
	return (e->exit_stat = 0);
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
