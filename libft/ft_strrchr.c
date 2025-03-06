/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vsoulas <vsoulas@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/24 09:12:54 by vsoulas           #+#    #+#             */
/*   Updated: 2024/10/28 09:57:27 by vsoulas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// look for the last occurence of char c in the array s
// return NULL if not found
// return position if found

#include "libft.h"

// char	*ft_strrchr(const char *s, int c);

// int	main(void)
// {
// 	char	s [] = "Hello World";
// 	char	c;

// 	c = 'l';
// 	printf("%s", ft_strrchr(s, c));
// 	return (0);
// }

char	*ft_strrchr(const char *s, int c)
{
	int	i;
	int	j;

	i = 0;
	j = -1;
	while (s[i] != '\0')
	{
		if ((unsigned char)s[i] == (unsigned char)c)
			j = i;
		i++;
	}
	if ((unsigned char)c == '\0')
		return ((char *)&s[i]);
	if (j != -1)
		return ((char *)&s[j]);
	return (NULL);
}
