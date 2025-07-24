/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdavtian <jdavtian@student.codam.nl>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/10 15:56:02 by vsoulas           #+#    #+#             */
/*   Updated: 2025/07/18 14:03:24 by jdavtian         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	line_read(t_command *command, int expand, t_expansion *e)
{
	char		*line;
	t_token		temp;

	(void)e;
	line = readline(">");
	if (!line)
		return (2);
	if (!ft_strcmp(line, command->heredoc_delimiter))
		return (free(line), 1);
	if (expand)
	{
		temp.input = ft_strdup(line);
		if (temp.input == NULL)
			return (error(3, NULL), free(line), 1);
		ft_variable_expansion(&temp, e);
		write(command->input_fd, temp.input, ft_strlen(temp.input));
		write(command->input_fd, "\n", 1);
		free((void *)temp.input);
		return (free(line), 0);
	}
	write(command->input_fd, line, ft_strlen(line));
	write(command->input_fd, "\n", 1);
	if (line)
		free(line);
	return (0);
}

void	ft_heredoc(t_command *command, t_expansion *e, int *expand)
{
	int	signal;

	signal = 0;
	rl_event_hook = forceout;
	while (g_heredoc_variable == 0)
	{
		signal = line_read(command, *expand, e);
		if (signal != 0)
			break ;
	}
	g_heredoc_variable = 0;
	sig_hand(MAIN);
}

void	readline_cleanup(t_command *command, t_expansion *e, char *filename)
{
	signal(SIGINT, &heredoc);
	close(command->input_fd);
	command->input_fd = open(filename, O_RDONLY);
	if (command->input_fd == -1)
	{
		ft_free_e(&e);
		unlink(filename);
		free(filename);
		perror("open");
		if (command->input_file)
			free(command->input_file);
		exit(EXIT_SUCCESS);
	}
	if (command->input_file)
		free(command->input_file);
	command->input_file = filename;
}

int	ft_delimiter(t_command *command, t_expansion *e, int *expand)
{
	int	quote;

	if (command->heredoc_delimiter[0] == 34
		|| command->heredoc_delimiter[0] == 39)
	{
		quote = command->heredoc_delimiter[0];
		if (ft_heredoc_delimiter(expand, &command->heredoc_delimiter) == 1)
			return (1);
		if (ft_remove_quotes_int(&command->heredoc_delimiter, quote) == 1)
			return (1);
	}
	else
	{
		if (ft_remove_quotes(&command->heredoc_delimiter) == 1)
			return (1);
	}
	sig_hand(HEREDOC);
	ft_heredoc(command, e, expand);
	return (0);
}

int	readline_here(t_command *command, t_expansion *e)
{
	int			expand;
	char		*tmpfile;

	expand = 1;
	tmpfile = ft_strdup("herefile");
	if (!tmpfile)
		return (error(3, NULL), 1);
	if (command->input_fd && command->input_file
		&& ft_strncmp(command->input_file, "herefile", 8) == 0)
		unlink(command->input_file);
	if (command->input_fd > 2)
		close(command->input_fd);
	command->input_fd = open(tmpfile, O_RDWR | O_CREAT | O_TRUNC, 0600);
	if (command->input_fd == -1)
		return (free(tmpfile), error(3, NULL), 1);
	if (ft_delimiter(command, e, &expand) == 1)
		return (free(tmpfile), error(3, NULL), 1);
	if (g_heredoc_variable == 1)
	{
		close(command->input_fd);
		command->input_fd = open(tmpfile, O_RDWR | O_CREAT | O_TRUNC, 0600);
	}
	readline_cleanup(command, e, tmpfile);
	return (0);
}
