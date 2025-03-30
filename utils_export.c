#include "parsing.h"

int	ft_replace_value(char *export, t_envp *current)
{
	free(current->value);
	current->value = copy_str_delimiter(export, 0);
	if (!current->value)
		return (1);
	return (0);
}

int	is_valid(char *str)
{
	int	i;

	if (str[0] != '_' && ft_isalpha(str[0]) == 0)
		return (1);
	i = 1;
	if (str[i])
	{
		while (str[i] && str[i] != '=')
		{
			if ((ft_isalnum(str[i]) == 0) && str[i] != '_')
				return (1);
			i++;
		}
	}
	return (0);
}

void	ft_print(t_envp **list, int total)
{
	int	i;

	i = 0;
	while (i < total)
	{
		printf("%s", list[i]->name);
		if (list[i]->value)
			printf("=%s", list[i]->value);
		printf("\n");
		i++;
	}
}
