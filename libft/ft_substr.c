/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vsoulas <vsoulas@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/24 09:13:47 by vsoulas           #+#    #+#             */
/*   Updated: 2024/10/28 16:22:40 by vsoulas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// substract "len" char from string s, starting at position "start"

#include "libft.h"

// char	*ft_substr(char const *s, unsigned int start, size_t len);

// int	main(void)
// {
// 	char			s [] = "Hello Codam";
// 	char			*duplicate;
// 	unsigned int	start;
// 	size_t			len;

// 	start = 0;
// 	len = 5;
// 	duplicate = ft_substr(s, start, len);
//	if (duplicate == NULL)
//		return (1);
// 	printf("%s\n", duplicate);
// 	free(duplicate);
// 	return (0);
// }

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*duplicate;
	size_t	s_len;

	s_len = ft_strlen(s);
	if (start >= s_len)
	{
		duplicate = (char *)malloc(1);
		if (duplicate == NULL)
			return (NULL);
		duplicate[0] = '\0';
		return (duplicate);
	}
	if (start + len > s_len)
		len = s_len - start;
	duplicate = (char *)malloc(len + 1);
	if (duplicate == NULL)
		return (NULL);
	ft_strlcpy(duplicate, s + start, len + 1);
	return (duplicate);
}
