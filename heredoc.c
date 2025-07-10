/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vsoulas <vsoulas@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/10 15:56:02 by vsoulas           #+#    #+#             */
/*   Updated: 2025/07/10 16:53:20 by vsoulas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

int	line_read(char *delim, int fd, int expand, t_expansion *e)
{
	char		*line;
	t_token		temp;

	line = readline(">");
	if (!line)
		return (1);
	if (!ft_strcmp(line, delim))
		return (free(line), 1);
	if (expand)
	{
		temp.input = ft_strdup(line);
		if (temp.input == NULL)
			error(3, NULL);
		ft_variable_expansion(&temp, e);
		write(fd, temp.input, ft_strlen(temp.input));
		write(fd, "\n", 1);
		free((void *)temp.input);
		free(line);
		return (0);
	}
	write(fd, line, ft_strlen(line));
	write(fd, "\n", 1);
	if (line)
		free(line);
	return (0);
}

void	ft_heredoc(char *deli, t_expansion *e, int fd, int *expand)
{
	rl_event_hook = forceout;
	while (g_heredoc_variable == 0)
	{
		if (line_read(deli, fd, *expand, e) != 0)
			break ;
	}
}

void	readline_cleanup(int fd, t_expansion *e, char *filename)
{
	signal(SIGINT, &heredoc);
	close(fd);
	fd = open(filename, O_RDONLY);
	if (fd == -1)
	{
		ft_free_e(&e);
		unlink(filename);
		free(filename);
		perror("open");
		exit(EXIT_FAILURE);
	}
	if (dup2(fd, STDIN_FILENO) == -1)
	{
		ft_free_e(&e);
		unlink(filename);
		free(filename);
		perror("dup2");
		exit(EXIT_FAILURE);
	}
	close(fd);
	unlink(filename);
	free(filename);
}

void	ft_pid_0(int fd, char *delim, t_expansion *e, int *expand)
{
	sig_hand(HEREDOC);
	ft_heredoc(delim, e, fd, expand);
	sig_hand(MAIN);
}

void	readline_here(char *delim, t_expansion *e)
{
	static char	heredoc_count = 'a';
	int			expand;
	int			fd;
	char		*tmpfile;

	expand = 1;
	tmpfile = ft_strjoin("herefile", &heredoc_count);
	++heredoc_count;
	fd = open(tmpfile, O_RDWR | O_CREAT | O_TRUNC, 0600);
	if (fd == -1)
		return (free(tmpfile), error(3, NULL));
	if (delim[0] == 34 || delim[0] == 39)
	{
		if (ft_heredoc_delimiter(&expand, &delim) == 1)
			exit(EXIT_FAILURE);
	}
	ft_pid_0(fd, delim, e, &expand);
	if (g_heredoc_variable == 1)
	{
		close(fd);
		fd = open(tmpfile, O_RDWR | O_CREAT | O_TRUNC, 0600); 
	}
	readline_cleanup(fd, e, tmpfile);
}
