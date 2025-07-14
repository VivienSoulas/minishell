/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vsoulas <vsoulas@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/18 14:25:10 by jdavtian          #+#    #+#             */
/*   Updated: 2025/05/30 13:35:36 by vsoulas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

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

	if (!getcwd(path, PATH_MAX))
		return (error(0, "getcwd error"), -1);
	env = find_node_env(envp, name);
	if (!env)
	{
		if (add_export_to_envp(envp, path, name) == 1)
			return (-1);
	}
	else
	{
		if (ft_replace_value(path, env) == 1)
			return (-1);
	}
	return (0);
}

int	cd(t_command *cmd, t_expansion *e)
{
	char	*target;
	int		i;

	i = 0;
	while (cmd->args[i])
		i++;
	if (i > 2)
		return (error(0, " too many arguments\n"), e->exit_stat = 1);
	if (i == 1)
	{
		target = get_env_value(&e->env, "HOME");
		if (!target)
			return (error(0, "HOME not set\n"), e->exit_stat = 1);
	}
	else
		target = cmd->args[1];
	if (target && !ft_strcmp(target, "~"))
	{
		target = get_env_value(&e->env, "HOME");
		if (!target)
			return (error(0, "HOME not set\n"), e->exit_stat = 1);
	}
	else if (target && target[0] == '$')
		return (1);
	if (update_node_with_cwd("OLDPWD", &e->env) == -1)
		return (e->exit_stat = 127);
	if (chdir(target) != 0)
		return (perror("cd"), e->exit_stat = 1);
	if (update_node_with_cwd("PWD", &e->env) == -1)
		return (e->exit_stat = 127);
	return (0);
}
