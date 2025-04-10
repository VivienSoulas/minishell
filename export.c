/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vsoulas <vsoulas@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/10 12:01:02 by vsoulas           #+#    #+#             */
/*   Updated: 2025/04/10 12:01:03 by vsoulas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

int	ft_crop(t_token *token)
{
	char	*value;

	value = copy_str_delimiter(token->input, 0);
	if (value == NULL)
		return (1);
	free(token->input);
	token->input = malloc(sizeof(char) * (ft_strlen(value) + 1));
	ft_memcpy(token->input, value, (ft_strlen(value) + 1));
	return (free(value), 0);
}

// check if value was already set and if so replace with new input
// if export is called, prints list of env + variable in order
// if no equal sign, prints only when export is called as VAR
// if no arg value VAR= only print when export is called
int	ft_export_check(t_envp **env, t_token **token, int *exit_stat)
{
	t_token	*current;

	current = (*token)->next;
	if (current == NULL)
		return (ft_print_export(env));
	while (current)
	{
		if (is_valid(current->input) == 0)
		{
			if (ft_strchr(current->input, '=') != 0)
			{
				if (ft_export_equal(current, exit_stat, env) == 1)
					return (1);
			}
			else if (add_export_to_envp(env, NULL, current->input) == 1)
				return (1);
		}
		else
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
		if (ft_strcmp(current->name, name) == 0)
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
	if (new->name == NULL)
		return (free(new), error(3, NULL), NULL);
	if (value == NULL)
		new->value = ft_strdup("");
	else
		new->value = ft_strdup(value);
	if (new->value == NULL)
		return (error(3, NULL), free(new->name), free(new), NULL);
	new->next = NULL;
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
