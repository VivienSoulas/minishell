/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_bzero.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vsoulas <vsoulas@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/24 09:02:04 by vsoulas           #+#    #+#             */
/*   Updated: 2024/10/28 12:00:43 by vsoulas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// used to set n bytes to the value 0 in the array s

#include "libft.h"

// int	main(void)
// {
// 	int 	*s = NULL;
// 	size_t	n;
// 	int		i;

// 	n = sizeof(s);
// 	i = 0;
// 	printf("before s =");
// 	while (i < 10)
// 	{
// 		printf("%d ", s[i]);
// 		i++;
// 	}
// 	printf("\n");
// 	ft_bzero(s, n);
// 	i = 0;
// 	printf("after s = ");
// 	while (i < 10)
// 	{
// 		printf("%d ", s[i]);
// 		i++;
// 	}
// 	return (0);
// }

void	ft_bzero(void *s, size_t n)
{
	size_t			i;
	unsigned char	*ptr;

	i = 0;
	ptr = (unsigned char *)s;
	while (i < n)
	{
		ptr[i] = 0;
		i++;
	}
}
