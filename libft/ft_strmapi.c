/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vsoulas <vsoulas@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/24 09:11:46 by vsoulas           #+#    #+#             */
/*   Updated: 2024/10/28 09:57:16 by vsoulas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// create a new array where the original string is
// changed through the function past in parameters

#include "libft.h"

// char	*ft_strmapi(char const *s, char (*f)(unsigned int, char));
//size_t	ft_strlen(const char *s);
// char	my_func(unsigned int i, char c);

// int	main(void)
// {
// 	char	s [] = "HELLO CODAM";
// 	char	*new_str;

// 	new_str = ft_strmapi(s, my_func);
// 	printf("%s\n", new_str);
// 	free(new_str);
// 	return (0);
// }

// char my_func(unsigned int i, char c)
// {
// 	printf("My inner function: index = %d and %c\n", i, c);
// 	return (c + 32);
// }

char	*ft_strmapi(char const *s, char (*f)(unsigned int, char))
{
	char			*new_str;
	unsigned int	i;

	i = 0;
	if (!s)
		return (NULL);
	new_str = (char *)malloc((ft_strlen(s) + 1) * sizeof(char));
	if (!new_str)
		return (NULL);
	while (s[i])
	{
		new_str[i] = f(i, s[i]);
		i++;
	}
	new_str[i] = '\0';
	return (new_str);
}
