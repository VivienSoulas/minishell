/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_variable_expansion.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vsoulas <vsoulas@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/10 12:01:36 by vsoulas           #+#    #+#             */
/*   Updated: 2025/04/10 12:01:37 by vsoulas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

char	*extract_name(char *input, t_expansion *exp)
{
	int		start;
	char	*name;
	int		len;

	start = exp->i;
	len = 0;
	while (input[start + len]
		&& ((ft_isalnum(input[start + len]) || input[start + len] == '_')))
		len++;
	exp->i = start + len;
	name = malloc(sizeof(char) * (len + 1));
	if (name == NULL)
		return (error(3, NULL), NULL);
	ft_memcpy(name, input + start, len);
	name[len] = '\0';
	return (name);
}

char	*get_env_value(t_envp **env, char *var_name)
{
	t_envp	*current;

	current = *env;
	while (current)
	{
		if (ft_strcmp(var_name, current->name) == 0)
			return (current->value);
		current = current->next;
	}
	return (NULL);
}

char	*ft_exit_status(char *res, t_expansion *exp)
{
	char	*exit_status;

	exit_status = ft_itoa((*exp->exit));
	if (exit_status == NULL)
		return (error(3, NULL), NULL);
	res = ft_strjoin_free(res, exit_status);
	if (res == NULL)
		return (free(exit_status), NULL);
	free(exit_status);
	exp->i++;
	return (res);
}
