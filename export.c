/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vsoulas <vsoulas@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/10 12:01:02 by vsoulas           #+#    #+#             */
/*   Updated: 2025/05/29 16:22:50 by vsoulas          ###   ########.fr       */
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
int	ft_export_check(t_token **token, t_expansion *e, int fd)
{
	t_token	*current;

	current = (*token)->next;
	if (current == NULL)
		return (ft_print_export(&e->export, fd, e));
	while (current)
	{
		if (is_valid(current, fd, e) == 0)
		{
			if (ft_strchr(current->input, '=') != 0)
			{
				if (ft_export_equal(current, e) == 1)
					return (e->exit_stat = 1);
			}
			else
			{
				if (add_export_to_export(&e->export, NULL, current->input) == 1)
					return (e->exit_stat = 1);
			}
		}
		else
			return (error(2, current->input), e->exit_stat = 1, 0);
		current = current->next;
	}
	return (0);
}

// export Z gets added to export list only
// export Z = without variable gets added to both with ""
// export Z = var gets added to both

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
	else
		new->value = ft_strdup(value);
	if (new->value == NULL)
		return (error(3, NULL), free(new->name), free(new), NULL);
	new->next = NULL;
	return (new);
}

// prints export list in alphabetic order
int	ft_print_export(t_export **export, int fd, t_expansion *e)
{
	t_export	**list;
	int			total;
	int			i;
	t_export	*current;

	current = *export;
	total = 0;
	while (current)
	{
		total++;
		current = current->next;
	}
	list = malloc(sizeof(t_export *) * (total + 1));
	if (list == NULL)
		return (error(3, NULL), 1);
	current = *export;
	i = 0;
	while (current)
	{
		list[i++] = current;
		current = current->next;
	}
	ft_sort_list((t_envp **)list, total);
	ft_print((t_envp **)list, total, fd);
	return (free(list), 0);
}
