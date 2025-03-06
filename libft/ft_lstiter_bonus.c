/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstiter_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vsoulas <vsoulas@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/28 09:55:53 by vsoulas           #+#    #+#             */
/*   Updated: 2024/10/28 09:55:53 by vsoulas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*Iterates the list ’lst’ and applies the function
’f’ on the content of each node.*/

#include "libft.h"

// #include <stdio.h>
// #include <stdlib.h>

// typedef struct s_list
// {
// 	int				*content;
// 	struct s_list	*next;
// }	t_list;

// void	f(void *data);
// void	ft_lstiter(t_list *lst, void (*f)(void *));

// t_list	*create_node(void *content)
// {
// 	t_list	*node;

// 	node = malloc (sizeof(t_list));
// 	if (!node)
// 		return (NULL);
// 	node->content = content;
// 	node->next = NULL;
// 	return (node);
// }

// void	f(void *data)
// {
// 	*(int *)data = 0;
// }

// int	main(void)
// {
// 	t_list	*node;
// 	t_list	*node1;
// 	int		i;
// 	int		*j;
// 	int		*k;
// 	int		l;

// 	i = 5;
// 	j = &i;
// 	l = 11;
// 	k = &l;
// 	node = create_node(j);
// 	node->next = create_node(k);
// 	node1 = node->next;
// 	printf("before %i, %i\n", *(node->content), *(node1->content));
// 	ft_lstiter(node, f);
// 	printf("after %i, %i\n", *(node->content), *(node1->content));
// 	return (0);
// }

void	ft_lstiter(t_list *lst, void (*f)(void *))
{
	if (!lst || !f)
		return ;
	while (lst)
	{
		f(lst->content);
		lst = lst->next;
	}
}
