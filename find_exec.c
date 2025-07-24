/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_exec.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vsoulas <vsoulas@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/30 14:08:02 by vsoulas           #+#    #+#             */
/*   Updated: 2025/05/30 14:08:03 by vsoulas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*find_executable_in_path(char *command)
{
	char	*res;

	if (access(command, X_OK) == 0)
	{
		res = ft_strdup(command);
		if (res == NULL)
			return (error(3, NULL), NULL);
		return (res);
	}
	return (NULL);
}

char	*find_executable_in_directory(char *command, char *directory)
{
	size_t	command_len;
	size_t	directory_len;
	char	*res;

	command_len = ft_strlen(command);
	directory_len = ft_strlen(directory);
	res = malloc(command_len + directory_len + 2);
	if (res == NULL)
		return (error(3, NULL), NULL);
	ft_memcpy(res, directory, directory_len);
	res[directory_len] = '/';
	ft_strlcpy(res + directory_len + 1, command, command_len + 1);
	if (access(res, X_OK) == 0)
		return (res);
	free(res);
	return (NULL);
}

void	free_directories(char **directories)
{
	int	i;

	i = -1;
	while (directories[++i])
		free(directories[i]);
	free(directories);
}

char	*find_executable(char *command, t_envp **envp_list)
{
	int		i;
	char	*path;
	char	**directories;
	char	*res;

	if (ft_strchr(command, '/'))
		return (find_executable_in_path(command));
	path = env_get_value(envp_list, "PATH");
	if (!path || !command || command[0] == '\0')
		return (NULL);
	directories = ft_split(path, ':');
	if (!directories)
		return (free(path), NULL);
	i = -1;
	while (directories[++i])
	{
		res = find_executable_in_directory(command, directories[i]);
		if (!res)
			continue ;
		free(path);
		free_directories(directories);
		return (res);
	}
	return (free(path), free_directories(directories), NULL);
}
