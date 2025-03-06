/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vsoulas <vsoulas@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/24 09:10:43 by vsoulas           #+#    #+#             */
/*   Updated: 2024/10/28 09:57:00 by vsoulas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

// size_t			ft_strlcat(char *dst, const char *src, size_t size);

// int	main(void)
// {
// 	char	src [] = " Codam";
// 	char	dst [20] = "Hello";
// 	size_t	size;
// 	size_t	len;

// 	size = 16;
// 	len = ft_strlcat(dst, src, size);
//     printf("Concatenated string: %s\n", dst);
//     printf("Total length: %zu\n", len);
// 	return (0);
// }

size_t	ft_strlcat(char *dst, const char *src, size_t size)
{
	size_t	i;
	size_t	j;
	size_t	src_len;
	size_t	dst_len;

	dst_len = 0;
	src_len = ft_strlen(src);
	while (dst[dst_len] && dst_len < size)
		dst_len++;
	i = dst_len;
	j = 0;
	if (size <= dst_len)
		return (size + src_len);
	if (size == 0)
		return (src_len);
	while (i < (size - 1) && src[j])
	{
		dst[i] = src[j];
		i++;
		j++;
	}
	dst[i] = '\0';
	return (src_len + dst_len);
}
