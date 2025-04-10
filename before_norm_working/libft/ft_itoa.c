/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vsoulas <vsoulas@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/24 09:07:51 by vsoulas           #+#    #+#             */
/*   Updated: 2024/10/28 11:19:36 by vsoulas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// create a new array with the conversion of int n into char *

#include "libft.h"

static int	ft_count(int n);

// int	main(void)
// {
//	char	*numbers;

//	numbers = ft_itoa(INT_MAX);
// 	printf("%s\n", numbers);
//	numbers = ft_itoa(INT_MIN);
// 	printf("%s\n", numbers);
//	numbers = ft_itoa(0);
// 	printf("%s\n", numbers);
//	free(numbers);
// 	return (0);
// }

char	*ft_itoa(int n)
{
	char	*numbers;
	int		count;

	if (n == INT_MIN)
		return (numbers = ft_strdup("-2147483648"));
	count = ft_count(n);
	numbers = (char *) malloc((count + 1) * sizeof(char));
	if (numbers == NULL)
		return (NULL);
	numbers[count] = '\0';
	if (n == 0)
		numbers[0] = '0';
	if (n < 0)
	{
		numbers[0] = '-';
		n = -n;
	}
	while (n > 0)
	{
		numbers[--count] = (n % 10 + '0');
		n = n / 10;
	}
	return (numbers);
}

static int	ft_count(int n)
{
	int		count;

	count = 0;
	if (n < 0)
	{
		n = -n;
		count++;
	}
	if (n == 0)
		return (1);
	while (n > 0)
	{
		n = n / 10;
		count++;
	}
	return (count);
}
