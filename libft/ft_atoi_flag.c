/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi_flag.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vsoulas <vsoulas@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/27 11:58:51 by vsoulas           #+#    #+#             */
/*   Updated: 2025/02/27 15:14:47 by vsoulas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

// int	ft_atoi(const char *nptr);
// int	main(void)
// {
// 	char	*nptr = NULL;
//	int		error = 0;
// 	printf("%d\n", ft_atoi(nptr, &error));
// 	return (0);
// }

int	ft_atoi_flag(char *str, int *error)
{
	int			i;
	int			sign;
	long long	number;

	i = 0;
	sign = 1;
	number = 0;
	if (str[i] == '-')
	{
		sign *= -1;
		i++;
	}
	else if (str[i] == '+')
		i++;
	while (str[i])
	{
		number = number * 10 + (str[i] - '0');
		if (number * sign > INT_MAX || number * sign < INT_MIN)
		{
			*error = 1;
			return (0);
		}
		i++;
	}
	return (number * sign);
}
