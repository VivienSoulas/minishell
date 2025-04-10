/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putchar_fd.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vsoulas <vsoulas@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/24 09:08:38 by vsoulas           #+#    #+#             */
/*   Updated: 2024/10/28 18:18:19 by vsoulas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// open or creat a file called char.txt and write the letter asigned to s in it

#include "libft.h"

// void	ft_putchar_fd(char s, int fd);

// int	main(void)
// {
// 	char	s;
// 	int		fd;

// 	s = 'A';
// 	fd = open("char.txt", O_RDWR | O_CREAT);
// 	if (fd == -1)
// 		return (1);
// 	ft_putchar_fd(s, fd);
// 	return (0);
// }

void	ft_putchar_fd(char s, int fd)
{
	write(fd, &s, 1);
}
