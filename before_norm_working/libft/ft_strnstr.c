/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vsoulas <vsoulas@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/24 09:12:46 by vsoulas           #+#    #+#             */
/*   Updated: 2024/10/28 09:57:23 by vsoulas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

// char	*ft_strnstr(const char *haystack, const char *needle, size_t len);

// int	main(void)
// {
// 	char	haystack [] = "Hello World";
// 	char	needle [] = "lo";
// 	size_t	len;

// 	len = 12;

// 	char *result = ft_strnstr(haystack, needle, len);

//     if (result)
// 	{
//         printf("Found: %s\n", result);
//     }
// 	else
// 	{
//         printf("Not found within the first %zu characters.\n", len);
//     }
//     return 0;
// }

char	*ft_strnstr(const char *haystack, const char *needle, size_t len)
{
	size_t	i;
	size_t	j;

	i = 0;
	if (!*needle)
		return ((char *)haystack);
	while (i < len && haystack[i])
	{
		j = 0;
		while (haystack[i + j] && needle[j]
			&& (i + j) < len && haystack[i + j] == needle[j])
			j++;
		if (!needle[j])
			return ((char *)haystack + i);
		i++;
	}
	return (NULL);
}
