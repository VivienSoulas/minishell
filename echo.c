/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vsoulas <vsoulas@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/10 15:55:34 by vsoulas           #+#    #+#             */
/*   Updated: 2025/07/18 11:14:24 by vsoulas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

int	echo_print(char *current, t_command *cmd, int fd)
{
	t_token	token;
	int		i;

	i = 1;
	if (current && !ft_strcmp(current, "-n"))
		current = cmd->args[++i];
	while (current)
	{
		token.input = ft_strdup(current);
		if (token.input == NULL)
			return (1);
		write(fd, token.input, ft_strlen(token.input));
		current = cmd->args[++i];
		if (current)
			write(fd, " ", 1);
		free(token.input);
		token.input = NULL;
	}
	return (0);
}

int	echo(t_command *cmd, int fd)
{
	int		no_new_line;
	char	*current;
	int		i;

	i = 1;
	no_new_line = 0;
	current = cmd->args[i];
	if (current && !ft_strcmp(current, "-n"))
	{
		no_new_line = 1;
	}
	if (echo_print(current, cmd, fd) == 1)
		return (1);
	if (!no_new_line)
		write(fd, "\n", 1);
	return (0);
}
