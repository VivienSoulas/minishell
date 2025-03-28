#include "parsing.h"

// check if value was already set and if so replace with new input
int	ft_export_check(t_envp **env, t_token **token)
{
	t_token	*current;

	current = *token;
	if (ft_strncmp(current->input, "export", 7) == 0 && current->prev == NULL)
	{
// should print envp sorted by alphabetic order cap first lower last
		if (current->next == NULL)
			return (printf("Invalid input, printing envp\n"), 0);
// if no equal sign, add VAR to export list only
		if (ft_strchr(current->next->input, '=') == 0)
			return (0);
// WORKING if no arg value = ""
		if (add_export_to_envp(env, current->next->input) == 1)
			return (1);
	}
	return (0);
}

int	add_export_to_envp(t_envp **env, char *export)
{
	t_envp	*current;
	t_envp	*prev;
	t_envp	*new;
	char	*name;
	int		len;

	name = copy_str_delimiter(export, 1);
	if (name == NULL)
		return (1);
	len = ft_strlen(name);
	current = *env;
	while (current)
	{
		if (ft_strncmp(current->name, name, len) == 0)
			return (ft_replace_value(export, current), 0);
		prev = current;
		current = current->next;
	}
	new = new_envp(export);
	if (new == NULL)
		return (1);
	new->next = NULL;
	if (prev != NULL)
		prev->next = new;
	else
		*env = new;
	return (0);
}

int	ft_replace_value(char *export, t_envp *current)
{
	char	*value;
	char	*equal;

	equal = ft_strchr(export, '=');
	value = copy_str_delimiter(export, 0);
	free(current->value);
	value = malloc(ft_strlen(equal + 1) + 1);
	if (!value)
		return (1);
	ft_strlcpy(value, equal + 1, ft_strlen(equal + 1) + 1);
	return (0);
}
