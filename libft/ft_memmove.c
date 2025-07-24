/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vsoulas <vsoulas@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/24 09:08:16 by vsoulas           #+#    #+#             */
/*   Updated: 2024/10/28 09:56:22 by vsoulas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// copy a n amount of bytes from src into dest with overlap handling

#include "libft.h"

// void	*ft_memmove(void *dest, const void *src, size_t n);

// int	main(void)
// {
// 	char	src [] = "Hello World";
// 	char	dest [12];
// 	size_t	n;

// 	n = 12;
// 	printf("dest = %s\n", ft_memmove(dest, src, n));
// 	printf("with overlap dest = %s\n", ft_memmove(src + 2, src, 5));
// 	return (0);
// }

// to do the backwards copying we first put
// ptr_src and ptr_dest at the end by adding n
// then we decrease n to 0 and copy the pointers
// value from on to the other while they decrease
// to copy forwards we also decrease the n to 0 but increase the pointers *
void	*ft_memmove(void *dest, const void *src, size_t n)
{
	unsigned char	*ptr_dest;
	unsigned char	*ptr_src;

	ptr_dest = (unsigned char *)dest;
	ptr_src = (unsigned char *)src;
	if (n == 0 || dest == src)
		return (dest);
	if (ptr_src < ptr_dest)
	{
		ptr_src = ptr_src + n;
		ptr_dest = ptr_dest + n;
		while (n--)
			*(--ptr_dest) = *(--ptr_src);
	}
	else
	{
		while (n--)
			*ptr_dest++ = *ptr_src++;
	}
	return (dest);
}
