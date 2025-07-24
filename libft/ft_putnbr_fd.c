/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vsoulas <vsoulas@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/24 09:08:56 by vsoulas           #+#    #+#             */
/*   Updated: 2025/02/27 15:15:13 by vsoulas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// open or create a file called nb.txt and write numbers in it

#include "libft.h"

void	ft_putnbr_fd(int n, int fd);
void	ft_putchar_fd(char s, int fd);
void	ft_putstr_fd(char *s, int fd);

//int	main(void)
//{
//	int	max;
//	int	min;
//	int	fd;
//	max = INT_MAX;
//	min = INT_MIN;
//	fd = open("nb.txt", O_RDWR | O_CREAT);
//	ft_putnbr_fd(max, fd);
//	ft_putnbr_fd(min, fd);
//	return (0);
//}

void	ft_putnbr_fd(int n, int fd)
{
	if (n == INT_MIN)
		ft_putstr_fd("-2147483648", fd);
	else
	{
		if (n < 0)
		{
			ft_putchar_fd('-', fd);
			n *= -1;
		}
		if (n >= 10)
			ft_putnbr_fd(n / 10, fd);
		ft_putchar_fd((n % 10) + '0', fd);
	}
}

//void	ft_putchar_fd(char s, int fd)
//{
//	write(fd, &s, 1);
//}

//void	ft_putstr_fd(char *s, int fd)
//{
//	int	i;

//	i = 0;
//	while (s[i])
//	{
//		write(fd, &s[i], 1);
//		i++;
//	}
//}
