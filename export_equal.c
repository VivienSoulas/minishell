/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_equal.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vsoulas <vsoulas@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/10 12:00:57 by vsoulas           #+#    #+#             */
/*   Updated: 2025/07/18 13:29:24 by vsoulas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

int	ft_export_equal(t_token *current, t_expansion *e)
{
	t_variable	*vari;

	vari = malloc(sizeof(t_variable));
	if (vari == NULL)
		return (error(3, NULL), 1);
	vari->name = copy_str_delimiter(current->input, 1);
	if (vari->name == NULL)
		return (free(vari), 1);
	vari->value = copy_str_delimiter(current->input, 0);
	if (vari->value == NULL)
		return (free(vari->name), free(vari), 1);
	if (vari->value[0] == '$'
		|| vari->value[0] == '\'' || vari->value[0] == '\"')
	{
		if (ft_dollar(current, vari, e) == 1)
			return (free(vari->name), free(vari->value), free(vari), 1);
	}
	else if (vari->value[0] == '\0')
	{
		free(vari->value);
		vari->value = NULL;
	}
	if (ft_export_env(e, vari) == 1)
		return (free(vari->name), free(vari->value), free(vari), 1);
	return (free(vari->name), free(vari->value), free(vari), 0);
}

int	ft_dollar(t_token *cur, t_variable *vari, t_expansion *e)
{
	(void)e;
	if (ft_crop(cur) == 1)
		return (free(vari->name), free(vari->value), 1);
	free(vari->value);
	vari->value = NULL;
	if (cur->input[0] != '\0' && cur->input[0] != '$')
	{
		vari->value = malloc(sizeof(char) * (ft_strlen(cur->input) + 1));
		if (vari->value == NULL)
			return (free(vari->name), error(3, NULL), 1);
		ft_memcpy(vari->value, cur->input, (ft_strlen(cur->input) + 1));
	}
	else
		vari->value = NULL;
	return (0);
}

int	ft_replace_value_export(char *export, t_export *current)
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

int	ft_export_env(t_expansion *e, t_variable *vari)
{
	if (add_export_to_envp(&e->env, vari->value, vari->name) == 1)
		return (free(vari->name), free(vari->value), free(vari), 1);
	if (add_export_to_export(&e->export, vari->value, vari->name) == 1)
		return (free(vari->name), free(vari->value), free(vari), 1);
	return (0);
}
