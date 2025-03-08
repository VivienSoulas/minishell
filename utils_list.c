#include "parsing.h"

t_token	*ft_new_node(char *content)
{
	t_token	*node;

	node = malloc(sizeof(t_token));
	if (node == NULL)
		return (NULL);
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
