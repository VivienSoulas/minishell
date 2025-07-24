/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstlast_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vsoulas <vsoulas@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/25 14:01:22 by vsoulas           #+#    #+#             */
/*   Updated: 2024/10/28 09:55:59 by vsoulas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// Returns the last node of the list.

#include "libft.h"

// #include <stdio.h>
// #include <stdlib.h>

// typedef struct s_list
// {
//    int content;
//    struct s_list *next;
// } t_list;

// t_list	*ft_lstlast(t_list *lst);
// int		ft_lstsize(t_list *lst);
// t_list	*create_node(int value);

// int	main(void)
// {
// 	t_list	*a;
// 	t_list	*last_node;

// 	a = create_node(1);
// 	a->next =  create_node(2);
// 	a->next->next = create_node(40);
// 	last_node = ft_lstlast(a);
// 	printf("The last node's content is : %d\n", last_node->content);
// 	return (0);
// }

// t_list	*create_node(int value)
// {
//    t_list *new_node = malloc(sizeof(t_list));
//    if (!new_node)
//        return NULL;
//    new_node->content = value;
//    new_node->next = NULL;
//    return (new_node);
// }

t_list	*ft_lstlast(t_list *lst)
{
	if (lst)
	{
		while (lst->next != NULL)
		{
			lst = lst->next;
		}
	}
	return (lst);
}
