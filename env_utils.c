/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vsoulas <vsoulas@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/10 12:00:50 by vsoulas           #+#    #+#             */
/*   Updated: 2025/04/18 14:42:33 by vsoulas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

int	ft_strcmp(const char *s1, const char *s2)
{
	while (*s1 && *s2 && *s1 == *s2)
	{
		s1++;
		s2++;
	}
	return (*s1 - *s2);
}

char	*env_get_value(t_envp **list, char *name)
{
	t_envp	*current;
	char	*res;

	current = *list;
	if (!list || !current || !name)
		return (NULL);
	while (current)
	{
		if (ft_strcmp(current->name, name) == 0)
		{
			res = ft_strdup(current->value);
			if (!res)
				return (error(3, NULL), NULL);
			return (res);
		}
		current = current->next;
	}
	return (NULL);
}

static int	count_list(t_envp **list)
{
	int		res;
	t_envp	*current;

	res = 0;
	current = *list;
	while (current)
	{
		res++;
		current = current->next;
	}
	return (res);
}

int	init_array(char **res, t_envp **list)
{
	t_envp	*current;
	int		i;
	int		n_len;
	int		v_len;

	i = 0;
	current = *list;
	while (current)
	{
		n_len = ft_strlen(current->name);
		v_len = ft_strlen(current->value);
		res[i] = malloc(n_len + v_len + 2);
		if (res[i] == NULL)
			return (error(3, NULL), -1);
		ft_memcpy(res[i], current->name, n_len);
		ft_memcpy(res[i] + n_len, "=", 1);
		ft_strlcpy(res[i] + n_len + 1, current->value, v_len + 1);
		current = current->next;
		i++;
	}
	res[i] = NULL;
	return (0);
}

char	**list_to_array(t_envp **list)
{
	int		count;
	char	**res;

	count = count_list(list);
	if (count == 0)
		return (NULL);
	res = (char **)malloc((count + 1) * sizeof(char *));
	if (!res)
		return (error(3, NULL), NULL);
	if (init_array(res, list) != 0)
		free_array(res);
	return (res);
}
