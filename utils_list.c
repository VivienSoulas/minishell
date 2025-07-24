/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_list.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vsoulas <vsoulas@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/10 12:01:30 by vsoulas           #+#    #+#             */
/*   Updated: 2025/04/10 12:01:31 by vsoulas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// create a linked list with each parts of the command (aka tokens)
int	ft_list_tokens(char **tokens, t_token **token)
{
	int		i;
	t_token	*node;

	i = 0;
	while (tokens[i])
	{
		node = ft_new_node(tokens[i]);
		if (node == NULL)
			return (1);
		ft_add_last(token, node);
		i++;
	}
	return (0);
}

t_token	*ft_new_node(char *content)
{
	t_token	*node;

	node = malloc(sizeof(t_token));
	if (node == NULL)
		return (error(3, NULL), NULL);
	node->input = ft_strdup(content);
	if (node->input == NULL)
		return (NULL);
	node->type = -1;
	node->next = NULL;
	node->prev = NULL;
	return (node);
}

void	ft_add_last(t_token **token, t_token *node)
{
	t_token	*last;

	if (token == NULL)
		return ;
	else if (*token == NULL)
		*token = node;
	else
	{
		last = ft_last(token);
		last->next = node;
		node->prev = last;
	}
}

t_token	*ft_last(t_token **token)
{
	t_token	*current;

	current = *token;
	if (current == NULL)
		return (NULL);
	while (current->next != NULL)
	{
		current = current->next;
	}
	return (current);
}
