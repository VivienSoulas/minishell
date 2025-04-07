#include "parsing.h"

int	ft_export_equal(t_token *current, int *exit_stat, t_envp **env)
{
	t_variable	*vari;

	vari = malloc(sizeof(t_variable));
	if (vari == NULL)
		return (error(3, NULL), 1);
	vari->name = copy_str_delimiter(current->input, 1);
	if (vari->name == NULL)
		return (1);
	vari->value = copy_str_delimiter(current->input, 0);
	if (vari->value == NULL)
		return (free(vari->name), free(vari), 1);
	if (vari->value[0] == '$')
	{
		if (ft_dollar(current, vari, env, exit_stat) == 1)
			return (free(vari->name), free(vari->value), free(vari), 1);
	}
	else if (vari->value[0] == '\0')
	{
		free(vari->value);
		vari->value = NULL;
	}
	if (add_export_to_envp(env, vari->value, vari->name) == 1)
		return (free(vari->name), free(vari->value), free(vari), 1);
	return (free(vari->name), free(vari->value), free(vari), 0);
}

int	ft_dollar(t_token *cur, t_variable *vari, t_envp **env, int *exit)
{
	if (ft_crop(cur) == 1)
		return (free(vari->name), free(vari->value), 1);
	if (ft_variable_expansion(cur, env, exit) == 1)
		return (free(vari->name), free(vari->value), 1);
	free(vari->value);
	vari->value = NULL;
	if (cur->input[0] != '\0' && cur->input[0] != '$')
	{
		vari->value = malloc(sizeof(char) * (ft_strlen(cur->input) + 1));
		if (vari->value == NULL)
			return (free(vari->name), error(3, NULL), 1);
		ft_memcpy(vari->value, cur->input, (ft_strlen(cur->input) + 1));
	}
	else
		vari->value = NULL;
	return (0);
}
