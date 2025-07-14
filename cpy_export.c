/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cpy_env.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vsoulas <vsoulas@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/21 13:17:37 by jdavtian          #+#    #+#             */
/*   Updated: 2025/03/28 17:19:31 by vsoulas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

t_export	*new_export(char *envp)
{
	t_export	*new;

	new = malloc(sizeof(t_export));
	if (new == NULL)
		return (error(3, NULL), NULL);
	new->name = copy_str_delimiter(envp, 1);
	if (new->name == NULL)
		return (error(3, NULL), free(new), NULL);
	new->value = copy_str_delimiter(envp, 0);
	if (new->value == NULL)
	{
		free(new->name);
		free(new);
		return (error(3, NULL), NULL);
	}
	new->next = NULL;
	return (new);
}

// check for failled new_envp
int	add_to_export(t_export **envp_list, char *envp)
{
	t_export	*temp;
	t_export	*new;

	if (*envp_list == NULL)
	{
		*envp_list = new_export(envp);
		if (*envp_list == NULL)
			return (1);
		return (0);
	}
	temp = *envp_list;
	while (temp->next)
		temp = temp->next;
	new = new_export(envp);
	if (new == NULL)
		return (1);
	temp->next = new;
	return (0);
}

t_export	*copy_export(char **envp)
{
	t_export	*envp_list;
	int			i;

	i = 0;
	envp_list = NULL;
	while (envp[i])
	{
		if (add_to_export(&envp_list, envp[i]) == 1)
			return (ft_free_export_list(&envp_list), NULL);
		i++;
	}
	return (envp_list);
}

int	add_export_to_export(t_export **env, char *value, char *name)
{
	t_export	*current;
	t_export	*prev;
	t_export	*new;

	current = *env;
	while (current)
	{
		if (ft_strcmp(current->name, name) == 0)
		{
			if (ft_replace_value_export(value, current) == 1)
				return (1);
			return (0);
		}
		prev = current;
		current = current->next;
	}
	new = ft_new_export_export(value, name);
	new->next = NULL;
	if (prev != NULL)
		prev->next = new;
	else
		*env = new;
	return (0);
}

t_export	*ft_new_export_export(char *value, char *name)
{
	t_export	*new;

	new = malloc(sizeof(t_export));
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
