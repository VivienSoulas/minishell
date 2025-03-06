/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_executable.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdavtian <jdavtian@student.codam.nl>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/04 12:51:47 by jdavtian          #+#    #+#             */
/*   Updated: 2025/03/04 15:13:48 by jdavtian         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

char	*find_by_path(char *cmd)
{
	char	*full_path;

	if (!access(cmd, X_OK))
	{
		full_path = ft_strdup(cmd);
		return (full_path);
	}
	return (NULL);
}

char	*find_in_dir(char *cmd, char *dir)
{
	size_t	cmd_len;
	size_t	dir_len;
	char	*full_path;

	cmd_len = ft_strlen(cmd);
	dir_len = ft_strlen(dir);
	full_path = malloc(cmd_len + dir_len + 2);
	if (full_path == NULL)
	{
		printf("Malloc failed\n");
		return (NULL);
	}
	ft_memcpy(full_path, dir, dir_len);
	full_path[dir_len + 1] = '/';
	ft_strlcpy(full_path + dir_len + 1, cmd, cmd_len + 1);
	if (!access(full_path, X_OK))
		return (full_path);
	free(full_path);
	return (NULL);
}

void	free_dirs(char **dirs)
{
	int	i;

	i = -1;
	while (dirs[++i])
		free(dirs[i]);
	free(dirs);
}

char	*find_executable(char *cmd, char **envp)
{
	int		i;
	char	*path;
	char	**dirs;
	char	*full_path;

	if (ft_strchr(cmd, '/'))
		return (find_by_path(cmd));
	path = getenv("PATH");
	if (!path || !cmd || cmd[0] == '\0')
		return (NULL);
	dirs = ft_split(path, ':');
	if (!dirs)
		return (NULL);
	i = -1;
	while (dirs[++i])
	{
		full_path = find_in_dir(cmd, dirs[i]);
		if (!full_path)
			continue ;
		free_dirs(dirs);
		return (full_path);
	}
	free_dirs(dirs);
	return (NULL);
}

int	main(int argc, char **argv, char **envp)
{
	char	*path;

	if (argc != 2)
		return (1);
	path = find_executable(argv[1], envp);
	if (!path)
	{
		printf("NO PATH \n");
	}
	else
		printf("Found path at %s\n", path);
	free (path);
	return (0);
}
