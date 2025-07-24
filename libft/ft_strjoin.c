/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vsoulas <vsoulas@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/24 09:10:27 by vsoulas           #+#    #+#             */
/*   Updated: 2024/10/28 17:12:53 by vsoulas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// concatinate two strings into a new array

#include "libft.h"

// char	*ft_strjoin(char const *s1, char const *s2);
//size_t	ft_strlen(const char *s);

// int	main(void)
// {
// 	char	*s1 = NULL;
// 	char	s2 [] = "Codam";
// 	char	*new_str;

// 	new_str = ft_strjoin(s1, s2);
// 	if (new_str == NULL)
// 		return (1);
// 	printf("%s\n", new_str);
// 	free(new_str);
// 	return (0);
// }

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*new_str;
	int		i;
	int		j;

	i = 0;
	j = 0;
	new_str = malloc((ft_strlen(s1) + ft_strlen(s2) + 1) * sizeof(char));
	if (new_str == NULL)
		return (NULL);
	while (s1[i])
	{
		new_str[i] = s1[i];
		i++;
	}
	while (s2[j])
	{
		new_str[i] = s2[j];
		i++;
		j++;
	}
	new_str[i] = '\0';
	return (new_str);
}
