/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vsoulas <vsoulas@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/24 09:11:01 by vsoulas           #+#    #+#             */
/*   Updated: 2024/10/28 09:57:07 by vsoulas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

//size_t			ft_strlcpy(char *dst, const char *src, size_t size);

// int	main(void)
// {
// 	char	src [] = "Hello Codam";
// 	char	dst [11];
// 	size_t	size;
// 	size_t	len;

// 	size = 16;
// 	len = ft_strlcpy(dst, src, size);
// 	printf("Destination: %s\n", dst);
// 	printf("Source length: %zu\n", len);
// 	return (0);

// }

size_t	ft_strlcpy(char *dst, const char *src, size_t size)
{
	size_t	i;

	i = 0;
	if (size == 0)
	{
		return (ft_strlen(src));
	}
	while (src[i] && i < size - 1)
	{
		dst[i] = src[i];
		i++;
	}
	dst[i] = '\0';
	return (ft_strlen(src));
}
