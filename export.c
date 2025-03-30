#include "parsing.h"

// check if value was already set and if so replace with new input
// if export is called, prints list of env + variable in order
// if no equal sign, prints only when export is called as VAR
// if no arg value VAR= only print when export is called
int	ft_export_check(t_envp **env, t_token **token)
{
	t_token	*current;

	current = *token;
	if (ft_strncmp(current->input, "export", 7) == 0 && current->prev == NULL)
	{
		if (current->next == NULL)
			return (ft_print_export(env), 0);
		if (is_valid(current->next->input) == 1)
			return (error(2, current->next->input), 0);
		if (ft_strchr(current->next->input, '=') == 0)
			return (0);
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

	name = copy_str_delimiter(export, 1);
	if (name == NULL)
		return (1);
	current = *env;
	while (current)
	{
		if (ft_strncmp(current->name, name, ft_strlen(name)) == 0)
			return (free(name), ft_replace_value(export, current), 0);
		prev = current;
		current = current->next;
	}
	new = new_envp(export);
	if (new == NULL)
		return (free(name), 1);
	new->next = NULL;
	if (prev != NULL)
		prev->next = new;
	else
		*env = new;
	return (free(name), 0);
}

// prints env in alphabetic order
void	ft_print_export(t_envp **env)
{
	t_envp	*current;

	current = *env;
	while (current)
	{
		printf("%s=%s\n", current->name, current->value);
		current = current->next;
	}
}
