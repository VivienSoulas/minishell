/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   buildin.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdavtian <jdavtian@student.codam.nl>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/10 12:00:40 by vsoulas           #+#    #+#             */
/*   Updated: 2025/04/18 14:25:04 by jdavtian         ###   ########.fr       */
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

int	exec_buildin(t_command *cmd, t_envp **envp, int *exit, t_token **t)
{
	int	fd;

	fd = STDOUT_FILENO;
	if (!ft_strcmp(cmd->args[0], "pwd"))
		pwd(envp);
	else if (!ft_strcmp(cmd->args[0], "unset"))
		unset(cmd, envp);
	else if (!ft_strcmp(cmd->args[0], "env"))
		env(envp);
	else if (!ft_strcmp(cmd->args[0], "echo"))
		echo(t, envp, exit, fd);
	else if (!ft_strcmp(cmd->args[0], "exit"))
		return (*exit = 1);
	else if (!ft_strcmp(cmd->args[0], "cd"))
		(cd(cmd, envp));
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

int	echo(t_token **token, t_envp **env, int *exit_stat, int fd)
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
	while (current && current->type == ARG)
	{
		if (ft_variable_expansion(current, env, exit_stat) == 1)
			return (1);
		write(fd, current->input, ft_strlen(current->input));
		if (current->next != NULL && current->next->type == ARG)
			write(fd, " ", 1);
		current = current->next;
	}
	if (!no_new_line)
		write(fd, "\n", 1);
	return (0);
}
