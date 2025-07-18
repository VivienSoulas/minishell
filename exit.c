/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdavtian <jdavtian@student.codam.nl>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/30 14:07:57 by vsoulas           #+#    #+#             */
/*   Updated: 2025/06/05 13:05:09 by jdavtian         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_isnum_exit(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if ((str[i] <= '9' && str[i] >= '0') || str[i] == '\"'
			|| str[i] == '+' || str[i] == '-')
			i++;
		else
			return (0);
	}
	return (1);
}

long	ft_atol_exit(const char *nptr)
{
	int	i;
	int	sign;
	int	number;

	i = 0;
	sign = 1;
	number = 0;
	while ((nptr[i] >= 9 && nptr[i] <= 13) || nptr[i] == ' '
		|| nptr[i] == '\"' || nptr[i] == '+')
		i++;
	if (nptr[i] == '-')
	{
		sign *= -1;
		i++;
	}
	else if (nptr[i] == '+')
		i++;
	if (nptr[i] == '\"')
		i++;
	while (nptr[i] >= '0' && nptr[i] <= '9')
	{
		number = number * 10 + (nptr[i] - '0');
		i++;
	}
	return (number * sign);
}

int	ft_exit(t_expansion *e, t_command *cmd)
{
	long	exit_st;

	if (cmd->args[1] == NULL)
	{
		printf("exit\n");
		ft_free_e(&e);
		exit(0);
	}
	if (!ft_isnum_exit(cmd->args[1]))
	{
		printf("exit\n");
		printf("exit: %s: numeric argument required\n", cmd->args[1]);
		ft_free_e(&e);
		exit(2);
	}
	if (cmd->args[2])
	{
		printf("exit: too many arguments\n");
		return (1);
	}
	printf("exit\n");
	exit_st = ft_atol_exit(cmd->args[1]);
	ft_free_e(&e);
	exit(exit_st % 256);
}
