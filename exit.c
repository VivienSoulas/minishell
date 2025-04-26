#include "parsing.h"

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

int	ft_atoi_exit(const char *nptr)
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
	if (cmd->args[2])
	{
		e->exit_stat = 1;
		error(5, NULL);
		return (e->exit = 1);
	}
	else if (cmd->args[1])
	{
		if (ft_isnum_exit(cmd->args[1]) == 1)
		{
			e->exit_stat = ft_atoi_exit(cmd->args[1]);
			return (e->exit = 1);
		}
		else
		{
			e->exit_stat = 2;
			error(4, NULL);
			return (e->exit = 1);
		}
	}
	return (0);
}
