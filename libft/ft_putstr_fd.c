/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putstr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vsoulas <vsoulas@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/24 09:09:05 by vsoulas           #+#    #+#             */
/*   Updated: 2024/10/28 18:16:22 by vsoulas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// open or creat a file called str.txt and write string s in it

#include "libft.h"

// void	ft_putstr_fd(char *s, int fd);

// int	main(void)
// {
// 	char	s [] = "Hello Codam 42";
// 	int		fd;

// 	fd = open("str.txt", O_RDWR | O_CREAT);
// 	if (fd == -1)
// 		return (1);
// 	ft_putstr_fd(s, fd);
// 	return (0);
// }

void	ft_putstr_fd(char *s, int fd)
{
	int	i;

	i = 0;
	while (s[i])
	{
		write(fd, &s[i], 1);
		i++;
	}
}
