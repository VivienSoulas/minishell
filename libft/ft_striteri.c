/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_striteri.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vsoulas <vsoulas@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/24 09:09:39 by vsoulas           #+#    #+#             */
/*   Updated: 2024/10/28 09:56:54 by vsoulas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// Passing a function via an arg

#include "libft.h"

// void	ft_striteri(char *s, void (*f)(unsigned int, char*));
// void	my_function(unsigned int i, char *c);

// int	main(void)
// {
// 	char	s [] = "HELLO CODAM";

// 	ft_striteri(s, my_function);
// 	return (0);
// }

// void	my_function(unsigned int i, char *c)
// {
// 	printf("string = %s, index = %i\n", c, i);
// }

void	ft_striteri(char *s, void (*f)(unsigned int, char*))
{
	unsigned int	i;

	i = 0;
	if (!s)
		return ;
	while (s[i])
	{
		f(i, &s[i]);
		i++;
	}
}
