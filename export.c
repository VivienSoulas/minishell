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
		{
			if (ft_print_export(env) == 1)
				return (1);
			return (0);
		}
		if (is_valid(current->next->input) == 1)
			return (error(2, current->next->input), 0); 
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

	new = malloc(sizeof(t_envp));
	if (new == NULL)
		return (error(3, NULL), 1);
	if (ft_strchr(export, '=') == 0)
		new->name = ft_strdup(export);
	else
		new->name = copy_str_delimiter(export, 1);
	if (new->name == NULL)
		return (error(3, NULL), free(new), 1);
	current = *env;
	while (current)
	{
		if (ft_strncmp(current->name, new->name, ft_strlen(new->name) + 1) == 0)
		{		
			if (ft_replace_value(export, current) == 1)
				return (free(new->name), free(new), 1);
			return (free(new->name), free(new), 0);
		}
		prev = current;
		current = current->next;
	}
	if (ft_strchr(export, '=') == 0)
		new->value = ft_strdup("");
	else
		new->value = copy_str_delimiter(export, 0);
	if (new->value == NULL)
		return (error(3, NULL), free(new->name), free(new), 1);
	new->next = NULL;
	if (prev != NULL)
		prev->next = new;
	else
		*env = new;
	return (0);
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

int	ft_compare_names(char *name1, char *name2)
{
	int	i;

	i = 0;
	while (name1[i] && name2[i])
	{
		if (ft_isupper(name1[i]) && ft_islower(name2[i]))
			return (-1);
		if (ft_islower(name1[i]) && ft_isupper(name2[i]))
			return (1);
		if (name1[i] != name2[i])
			return (name1[i] - name2[i]);
		i++;
	}
	return (name1[i] - name2[i]);
}
