/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   buildin.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vsoulas <vsoulas@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/10 12:00:40 by vsoulas           #+#    #+#             */
/*   Updated: 2025/05/29 17:35:57 by vsoulas          ###   ########.fr       */
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
		"/bin/echo"
	};
	int			i;

	i = 0;
	while (i < 7)
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
	{
		if (cmd->args[1])
			return (printf("env: too many arguments\n"), e->exit_stat = 0);
		return (env(&e->env, t, e), e->exit_stat);
	}
	else if (!ft_strcmp(cmd->args[0], "echo")
		|| !ft_strcmp(cmd->args[0], "/bin/echo"))
		return (echo(t, e, fd), e->exit_stat = 0);
	else if (!ft_strcmp(cmd->args[0], "exit"))
		return (ft_exit(e, cmd));
	else if (!ft_strcmp(cmd->args[0], "cd"))
		return (cd(cmd, e), e->exit_stat = 1);
	return (e->exit);
}

int	env(t_envp **env, t_token **t, t_expansion *e)
{
	t_envp	*current;

	current = *env;
	if ((*t)->next)
	{
		printf(" Permission denied\n");
		return (error(0, (*t)->next->input), e->exit_stat = 126);
	}
	while (current)
	{
		if (current->value != NULL && ft_strncmp(current->value, "", 1) != 0)
			printf("%s=%s\n", current->name, current->value);
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

int	echo(t_token **token, t_expansion *e, int fd)
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
		if (ft_variable_expansion(current, e) == 1)
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
