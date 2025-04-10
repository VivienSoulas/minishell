/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vsoulas <vsoulas@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/24 09:02:18 by vsoulas           #+#    #+#             */
/*   Updated: 2024/10/28 11:17:29 by vsoulas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// used to create an array of size nmemb * sizeof and set it to 0

#include "libft.h"

// int	main(void)
// {
// 	size_t	nmemb;
// 	size_t		i;
// 	int		*new_array;
// 	char	*str;
// 	char	str1 [] = "Hello World";

// 	nmemb = 5;
// 	i = 0;
// 	new_array = (int *)ft_calloc(nmemb, sizeof(int));
// 	if (new_array == NULL)
// 		return (1);
// 	while (i < nmemb)
// 	{
// 		printf("%i", new_array[i]);
// 		i++;		
// 	}
// 	str = (char *)ft_calloc(nmemb, sizeof(char));
// 	if (str == NULL)
// 		return (1);
// 	strncpy(str, str1, nmemb);
// 	str[nmemb - 1] = '\0';
// 	printf("\n%s", str);
// 	free(new_array);
// 	free(str);
// 	return (0);
// }

void	*ft_calloc(size_t nmemb, size_t size)
{
	unsigned char	*ptr;
	size_t			i;
	size_t			total;

	total = nmemb * size;
	i = 0;
	ptr = (unsigned char *)malloc(total);
	if (ptr == NULL)
		return (NULL);
	while (i < total)
	{
		ptr[i] = 0;
		i++;
	}
	return (ptr);
}
