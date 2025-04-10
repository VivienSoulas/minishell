/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vsoulas <vsoulas@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/24 09:13:32 by vsoulas           #+#    #+#             */
/*   Updated: 2024/10/28 11:31:53 by vsoulas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

// char		*ft_strtrim(char const *s1, char const *set);

// int	main(void)
// {
// 	char	s1 [] = "\200 123Hello\200 123";
// 	char	set [] = "\200 123";
// 	char	*new_str;

// 	new_str = ft_strtrim(s1, set);
// 	if (new_str == NULL)
// 		return (1);
// 	printf("%s\n", new_str);
// 	return (0);
// }

char	*ft_strtrim(char const *s1, char const *set)
{
	char		*new_str;
	const char	*start;
	const char	*end;
	size_t		length;

	if (!s1)
		return (NULL);
	start = s1;
	while (*start && (ft_strrchr(set, *start) != NULL))
		start++;
	end = s1 + ft_strlen(s1) - 1;
	while (end > start && ft_strrchr(set, *end))
		end--;
	length = end - start + 1;
	new_str = (char *)malloc((length + 1) * sizeof(char));
	if (new_str == NULL)
		return (NULL);
	ft_strlcpy(new_str, start, length + 1);
	return (new_str);
}
