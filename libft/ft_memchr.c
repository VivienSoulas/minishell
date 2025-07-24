/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vsoulas <vsoulas@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/24 09:08:00 by vsoulas           #+#    #+#             */
/*   Updated: 2024/10/28 09:56:13 by vsoulas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// use to find the position (within n) of a char in an array

#include "libft.h"

// void	*ft_memchr(const void *s, int c, size_t n);

// int	main(void)
// {
// 	char	s [] = "Hello World";
// 	int		c;
// 	size_t	n;
// 	char	*result;

// 	c = 'o';
// 	n = 6;
// 	result = (char *)ft_memchr(s, c, n);
// 	if (result != NULL)
// 	{
//         printf("Character '%c' found at position: %lld\n", c, result - s);
//     }
// 	else
// 	{
//         printf("Character '%c' not found in the string.\n", c);
//     }
// 	return (0);
// }

void	*ft_memchr(const void *s, int c, size_t n)
{
	unsigned char	*ptr;
	size_t			i;

	i = 0;
	ptr = (unsigned char *)s;
	while (i < n)
	{
		if (ptr[i] == (unsigned char)c)
			return (ptr + i);
		i++;
	}
	return (NULL);
}
