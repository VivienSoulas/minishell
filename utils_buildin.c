#include "parsing.h"

int	ft_check_invalid(char *arg, t_envp **env)
{
	t_envp	*current;

	current = *env;
	if (arg[0] != '$')
		return (1);
	while (current)
	{
		if (ft_strcmp(arg + 1, current->name) == 0)
			return (1);
		current = current->next;
	}
	return (0);
}
