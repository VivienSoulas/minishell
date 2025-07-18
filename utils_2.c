/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vsoulas <vsoulas@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/18 13:00:28 by vsoulas           #+#    #+#             */
/*   Updated: 2025/07/18 13:29:49 by vsoulas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

int	ft_remove_quotes(char **delimiter)
{
	int		i;
	int		j;
	int		len;
	char	*temp;

	i = 0;
	j = 0;
	len = ft_strlen((*delimiter));
	temp = malloc(len + 1);
	if (!temp)
		return (1);
	while (i < len)
	{
		if ((*delimiter)[i] != '\'' && (*delimiter)[i] != '\"')
		{
			temp[j] = (*delimiter)[i];
			j++;
		}
		i++;
	}
	temp[j] = '\0';
	free(*delimiter);
	*delimiter = temp;
	return (0);
}

int	ft_remove_quotes_int(char **delimiter, int first_quote)
{
	int		i;
	int		j;
	int		len;
	char	*temp;

	i = 0;
	j = 0;
	len = ft_strlen((*delimiter));
	temp = malloc(len + 1);
	if (!temp)
		return (1);
	while (i < len)
	{
		if ((*delimiter)[i] != first_quote)
		{
			temp[j] = (*delimiter)[i];
			j++;
		}
		i++;
	}
	temp[j] = '\0';
	free(*delimiter);
	*delimiter = temp;
	return (0);
}

int	ft_variable(t_token **token, t_expansion *e)
{
	t_token	*current;

	current = *token;
	while (current)
	{
		if (current->prev && ft_strcmp(current->prev->input, "<<") == 0)
		{
			current = current->next;
			continue ;
		}
		if (ft_variable_expansion(current, e) == 1)
			return (1);
		current = current->next;
	}
	ft_assign_types(*token);
	return (0);
}
