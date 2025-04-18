/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdavtian <jdavtian@student.codam.nl>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/18 14:25:10 by jdavtian          #+#    #+#             */
/*   Updated: 2025/04/18 14:25:21 by jdavtian         ###   ########.fr       */
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

	env = find_node_env(envp, name);
	if (!env)
		return (error(0, "env parameter not found\n"), -1);
	if (!getcwd(path, PATH_MAX))
		return (error(0, "gwtcwd error"), -1);
	ft_replace_value(path, env);
	return (0);
}

int	cd(t_command *cmd, t_envp **envp)
{
	char	*target;
	int		i;

	(void)envp;
	i = 0;
	while (cmd->args[i])
		i++;
	if (i > 2)
		return (error(0, "too many arguments"), -1);
	if (i == 1)
		target = get_env_value(envp, "HOME");
	else
		target = cmd->args[1];
	if (!ft_strcmp(target, "~"))
		target = get_env_value(envp, "HOME");
	if (update_node_with_cwd("OLDPWD", envp) == -1)
		return (-1);
	if (chdir(target) != 0)
		return (perror("cd"), -1);
	if (update_node_with_cwd("PWD", envp) == -1)
		return (-1);
	return (0);
}
