/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_export.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vsoulas <vsoulas@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/10 12:01:27 by vsoulas           #+#    #+#             */
/*   Updated: 2025/05/29 16:24:30 by vsoulas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

int	is_valid(t_token *current)
{
	int	i;

	if (current->type >= CMD && current->type <= APPEND)
		return (printf("command to be interpreted here\n"), 0); // work to do here
	else if (current->input[0] != '_' && ft_isalpha(current->input[0]) == 0)
		return (1);
	i = 1;
	if (current->input[i])
	{
		while (current->input[i] && current->input[i] != '=')
		{
			if ((ft_isalnum(current->input[i]) == 0) && current->input[i] != '_')
				return (1);
			i++;
		}
	}
	return (0);
}

int	ft_replace_value(char *export, t_envp *current)
{
	char	*new_value;

	new_value = "";
	if (export)
	{
		new_value = ft_strdup(export);
		if (new_value == NULL)
			return (error(3, NULL), 1);
	}
	else
	{
		new_value = ft_strdup("''");
		if (new_value == NULL)
			return (error(3, NULL), 1);
	}
	if (current->value)
		free(current->value);
	current->value = new_value;
	return (0);
}

void	ft_print(t_envp **list, int total)
{
	int	i;

	i = 0;
	while (i < total)
	{
		printf("declare -x %s", list[i]->name);
		if (list[i]->value)
			printf("=%s", list[i]->value);
		printf("\n");
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
