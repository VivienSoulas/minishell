#include "parsing.h"

int	ft_crop(t_token *token)
{
	char	*value;

	value = copy_str_delimiter(token->input, 0);
	if (value == NULL)
		return (1);
	free(token->input);
	token->input = malloc(sizeof(char) * (ft_strlen(value) + 1));
	ft_memcpy(token->input, value, ft_strlen(value) + 1);
	return (free(value), 0);
}

// check if value was already set and if so replace with new input
// if export is called, prints list of env + variable in order
// if no equal sign, prints only when export is called as VAR
// if no arg value VAR= only print when export is called
int	ft_export_check(t_envp **env, t_token **token, int *exit_stat)
{
	t_token	*current;
	char	*name;
	char 	*value;

	current = (*token)->next;
	if (current == NULL)
	{
		if (ft_print_export(env) == 1)
			return (1);
		return (0);
	}
	while (current)
	{
		if (is_valid(current->input) == 0)
		{
			if (ft_strchr(current->input, '=') != 0)
			{
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
					value = malloc(sizeof(char) * ft_strlen(current->input) + 1);
					if (value == NULL)
						return (error(3, NULL), 1);
					ft_memcpy(value, current->input, ft_strlen(current->input));
				}
				else if (value[0] == '\0')
				{
					if (ft_crop(current) == 1)
						return (free(name), free(value), 1);
				}
				if (add_export_to_envp(env, value, name) == 1)
					return (free(name), free(value), 1);
			}
			else if (add_export_to_envp(env, "", current->input) == 1)
				return (1);
		}
		else if (is_valid(current->input) == 1)
			error(2, current->input);
		current = current->next;
	}
	return (0);
}

int	add_export_to_envp(t_envp **env, char *value, char *name)
{
	t_envp	*current;
	t_envp	*prev;
	t_envp	*new;

	current = *env;
	while (current)
	{
		if (ft_strncmp(current->name, name, ft_strlen(name) + 1) == 0)
		{
			if (ft_replace_value(value, current) == 1)
				return (1);
			return (0);
		}
		prev = current;
		current = current->next;
	}
	new = ft_new_export(value, name);
	new->next = NULL;
	if (prev != NULL)
		prev->next = new;
	else
		*env = new;
	return (0);
}

t_envp	*ft_new_export(char *value, char *name)
{
	t_envp	*new;
	
	new = malloc(sizeof(t_envp));
	if (new == NULL)
		return (error(3, NULL), NULL);
	new->name = ft_strdup(name);
	if (value == NULL)
		new->value = ft_strdup("");
	else
		new->value = ft_strdup(value);
	if (new->name == NULL || new->value == NULL)
		return (error(3, NULL), free(new), NULL);
	return (new);
}

// prints env in alphabetic order
int	ft_print_export(t_envp **env)
{
	t_envp	**list;
	int		total;
	int		i;
	t_envp	*current;

	current = *env;
	total = 0;
	while (current)
	{
		total++;
		current = current->next;
	}
	list = malloc(sizeof(t_envp *) * (total + 1));
	if (list == NULL)
		return (error(3, NULL), 1);
	current = *env;
	i = 0;
	while (current)
	{
		list[i++] = current;
		current = current->next;
	}
	ft_sort_list(list, total);
	ft_print(list, total);
	return (free(list), 0);
}

// sort the lsit of envp pointers
void	ft_sort_list(t_envp **list, int total)
{
	int		i;
	int		j;
	t_envp	*temp;

	i = 0;
	while (i < total)
	{
		j = 0;
		while (j < total - i - 1)
		{
			if (ft_compare_names(list[j]->name, list[j + 1]->name) > 0)
			{
				temp = list[j];
				list[j] = list[j + 1];
				list[j + 1] = temp;
			}
			j++;
		}
		i++;
	}
}
