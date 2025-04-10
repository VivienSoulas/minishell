/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vsoulas <vsoulas@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/24 09:09:31 by vsoulas           #+#    #+#             */
/*   Updated: 2025/04/04 14:58:16 by vsoulas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// use to duplicate a string into a new array

#include "libft.h"

// char		*ft_strdup(const char *s);

// int	main(void)
// {
// 	char	original [] = "Codam is cool";
// 	char	*duplicate;

// 	duplicate = ft_strdup(original);
// 	if (duplicate == NULL)
// 		return (1);
// 	printf("%s\n", duplicate);
// 	free(duplicate);
// 	return (0);
// }

char	*ft_strdup(const char *s)
{
	char	*str;
	int		total;
	int		i;

	i = 0;
	total = ft_strlen(s);
	str = (char *)malloc(total + 1);
	if (str == NULL)
		return (NULL);
	while (i < total)
	{
		str[i] = s[i];
		i++;
	}
	str[i] = '\0';
	return (str);
}
