#include "parsing.h"

int	ft_export_equal(t_token *current, int *exit_stat, t_envp **env)
{
	char	*name;
	char 	*value;

	name = copy_str_delimiter(current->input, 1);
	value = copy_str_delimiter(current->input, 0);
	if (name == NULL || value == NULL)
		return (1);
	if (value[0] == '$')
	{
		if (ft_crop(current) == 1)
			return (free(name), free(value), 1);
		if (ft_variable_expansion(current, env, exit_stat) == 1)
			return (free(name), free(value), 1);
		free(value);
		if (current->input[0] != '\0' && current->input[0] != '$')
		{
			value = malloc(sizeof(char) * ft_strlen(current->input) + 1);
			if (value == NULL)
				return (error(3, NULL), 1);
			ft_memcpy(value, current->input, ft_strlen(current->input));
		}
		else
			value = NULL;
	}
	else if (value[0] == '\0')
		value = NULL;
	if (add_export_to_envp(env, value, name) == 1)
		return (free(name), free(value), 1);
	return (0);
}
