/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putendl_fd.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vsoulas <vsoulas@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/24 09:08:46 by vsoulas           #+#    #+#             */
/*   Updated: 2024/10/28 09:56:28 by vsoulas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// open or create a file and write a string on it followed by a new line

#include "libft.h"

// void	ft_putendl_fd(char *s, int fd);

// int	main(void)
// {
// 	char	s [] = "Codam 42";
// 	int		fd;

// 	fd = open("trial.txt", O_RDWR | O_CREAT);
// 	if (fd == -1)
// 		return (1);
// 	ft_putendl_fd(s, fd);
// 	return (0);
// }

void	ft_putendl_fd(char *s, int fd)
{
	int	i;

	i = 0;
	while (s[i])
	{
		write(fd, &s[i], 1);
		i++;
	}
	write(fd, "\n", 1);
}
