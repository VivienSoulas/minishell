/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vsoulas <vsoulas@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/07 15:57:42 by jdavtian          #+#    #+#             */
/*   Updated: 2025/03/13 15:17:52 by vsoulas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

static int	get_home_and_current_dir(char **home_dir, char **current_dir)
{
	*current_dir = getcwd(NULL, 0);
	if (!*current_dir)
	{
		perror("getcwd");
		return (1);
	}
	*home_dir = getenv("HOME");
	if (!*home_dir)
	{
		free(*current_dir);
		printf("Home directory can't be found.\n");
		return (1);
	}
	return (0);
}

static char	*normalize_path(char *home_dir, char *current_dir, char *path)
{
	(void)current_dir;
	if (!path || *path == '\0' || (*path == '~' && *(path + 1) == '\0'))
	{
		return (home_dir);
	}
	return (path);
}

int	ft_cd(t_command *command)
{
	char	*home_dir;
	char	*current_dir;
	char	*norm_path;

	if (get_home_and_current_dir(&home_dir, &current_dir) != 0)
		exit (EXIT_FAILURE);
	norm_path = normalize_path(home_dir, current_dir, command->args[1]);
	if (chdir(norm_path) == -1)
	{
		perror("cd");
		exit (EXIT_FAILURE);
	}
	free (current_dir);
	exit (EXIT_SUCCESS);
}
