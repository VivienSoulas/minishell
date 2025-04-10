/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vsoulas <vsoulas@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/24 09:08:07 by vsoulas           #+#    #+#             */
/*   Updated: 2024/10/28 09:56:15 by vsoulas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// same as strncmp but with any kind of array

#include "libft.h"

// int	ft_memcmp(const void *s1, const void *s2, size_t n);

// int	main(void)
// {
// 	char	s1 [] = "Hello World";
// 	char	s2 [] = "Helo World";
// 	size_t	n;

// 	n = 9;
// 	printf("The difference is : %i\n", ft_memcmp(s1, s2, n));
// 	return (0);
// }

int	ft_memcmp(const void *s1, const void *s2, size_t n)
{
	unsigned char	*str1;
	unsigned char	*str2;
	size_t			i;

	i = 0;
	str1 = (unsigned char *) s1;
	str2 = (unsigned char *) s2;
	if (n == 0)
		return (0);
	while (i < n)
	{
		if (str1[i] != str2[i])
			return (str1[i] - str2[i]);
		i++;
	}
	return (0);
}
