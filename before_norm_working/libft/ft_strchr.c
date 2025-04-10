/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vsoulas <vsoulas@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/24 09:09:22 by vsoulas           #+#    #+#             */
/*   Updated: 2024/10/28 09:56:48 by vsoulas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// look for the first occurence of char c in the array s
// return NULL if not found
// return position if found

#include "libft.h"

// char	*ft_strchr(const char *s, int c);

// int	main(void)
// {
// 	char	s [] = "Hello World";
// 	char	c;

// 	c = '\0';
// 	printf("%s", ft_strchr(s, c));
// 	return (0);
// }

char	*ft_strchr(const char *s, int c)
{
	unsigned int	i;

	i = 0;
	while (s[i] != '\0')
	{
		if ((unsigned char)s[i] == (unsigned char)c)
			return ((char *)&s[i]);
		i++;
	}
	if ((unsigned char)c == '\0')
		return ((char *)&s[i]);
	return (NULL);
}
