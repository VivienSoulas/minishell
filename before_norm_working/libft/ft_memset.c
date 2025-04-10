/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vsoulas <vsoulas@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/24 09:08:25 by vsoulas           #+#    #+#             */
/*   Updated: 2024/10/28 09:56:24 by vsoulas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// use to set a certain amount n in the array s to a preset value c

#include "libft.h"

// void	*ft_memset(void *s, int c, size_t n);

// int	main(void)
// {
// 	int		c;
// 	size_t	n;
// 	char	s [] = "Hello World";
// 	char	s1 [] = "Hello World";

// 	c = 'A';
// 	n = 10;
// 	printf("before s = %s\n", s);
// 	ft_memset(s, c, n);
// 	printf("after s = %s\n", s);
// 	memset(s1, c, n);
// 	printf("original memset: %s\n", s1);
// 	return (0);
// }

void	*ft_memset(void *s, int c, size_t n)
{
	size_t			i;
	unsigned char	*ptr;

	i = 0;
	ptr = (unsigned char *)s;
	while (i < n)
	{
		ptr[i] = (unsigned char)c;
		i++;
	}
	return (s);
}
