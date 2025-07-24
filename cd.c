/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdavtian <jdavtian@student.codam.nl>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/18 14:25:10 by jdavtian          #+#    #+#             */
/*   Updated: 2025/07/18 12:23:34 by jdavtian         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_envp	*find_node_env(t_envp **list, char *name)
{
	t_envp	*node;

	node = *list;
	while (node)
	{
		if (!ft_strcmp(name, node->name))
			return (node);
		node = node->next;
	}
	return (NULL);
}

int	update_node_with_cwd(char *name, t_envp **envp)
{
	t_envp	*env;
	char	path[PATH_MAX];
	char	*current_path;

	if (!getcwd(path, PATH_MAX))
	{
		error(0, "getcwd error\n");
		current_path = "(unknown)";
	}
	else
		current_path = path;
	env = find_node_env(envp, name);
	if (!env)
	{
		if (add_export_to_envp(envp, current_path, name) == 1)
			return (-1);
	}
	else
	{
		if (ft_replace_value(current_path, env) == 1)
			return (-1);
	}
	return (0);
}

void	add_paremeter_env(char *name, t_expansion *e)
{
	char	path[PATH_MAX];

	if (!getcwd(path, PATH_MAX))
	{
		error(0, "getcwd");
		add_export_to_envp(&e->env, "(unknown)", name);
		return ;
	}
	add_export_to_envp(&e->env, path, name);
}

int	check_args(t_command *cmd, t_expansion *e, char **target)
{
	int	i;

	i = 0;
	while (cmd->args[i])
		i++;
	if (i > 2)
		return (error(0, " too many arguments\n"), e->exit_stat = 1, 1);
	if (i == 1)
		*target = get_env_value(&e->env, "HOME");
	else
		*target = cmd->args[1];
	return (0);
}

int	cd(t_command *cmd, t_expansion *e)
{
	char	*target;

	if (find_node_env(&e->env, "OLDPWD") == NULL)
		add_paremeter_env("OLDPWD", e);
	if (check_args(cmd, e, &target))
		return (1);
	if (target && !ft_strcmp(target, "~"))
		target = get_env_value(&e->env, "HOME");
	else if (target && target[0] == '$')
		return (e->exit_stat = 1);
	if (update_node_with_cwd("OLDPWD", &e->env) == -1)
		return (e->exit_stat = 127);
	if (chdir(target) != 0)
		return (perror("cd"), e->exit_stat = 1);
	if (find_node_env(&e->env, "PWD") == NULL)
		add_paremeter_env("PWD", e);
	if (update_node_with_cwd("PWD", &e->env) == -1)
		return (e->exit_stat = 127);
	return (e->exit_stat = 0);
}
