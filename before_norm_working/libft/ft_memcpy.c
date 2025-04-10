/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vsoulas <vsoulas@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/24 09:17:08 by vsoulas           #+#    #+#             */
/*   Updated: 2024/10/28 14:25:30 by vsoulas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// copy n byte from src into dest

#include "libft.h"

// void	*ft_memcpy(void *dest, const void *src, size_t n);

// int	main(void)
// {
// 	size_t	n;
// 	char	src [] = "Hello world";
// 	char	dest [12];

// 	n = 9;
// 	ft_memcpy(dest, src, n);
// 	dest [n] = '\0';
// 	printf("%s\n", dest);
// 	return (0);
// }

void	*ft_memcpy(void *dest, const void *src, size_t n)
{
	unsigned char	*ptr;
	unsigned char	*ptr1;
	size_t			i;

	ptr = (unsigned char *) dest;
	ptr1 = (unsigned char *) src;
	i = 0;
	if (dest == NULL && src == NULL)
		return (NULL);
	while (i < n)
	{
		ptr[i] = ptr1[i];
		i++;
	}
	return (dest);
}
