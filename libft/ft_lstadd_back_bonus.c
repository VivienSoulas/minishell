/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstadd_back_bonus.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vsoulas <vsoulas@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/25 14:07:26 by vsoulas           #+#    #+#             */
/*   Updated: 2024/10/28 09:55:41 by vsoulas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// Adds the node ’new’ at the end of the list.

#include "libft.h"

//#include <stdio.h>
//#include <stdlib.h>

//typedef struct s_list
//{
//    int content;
//    struct s_list *next;
//} t_list;

//void	ft_lstadd_back(t_list **lst, t_list *new);

//t_list	*create_node(int value)
//{
//    t_list *new_node = malloc(sizeof(t_list));
//    if (!new_node)
//        return NULL;
//    new_node->content = value;
//    new_node->next = NULL;
//    return (new_node);
//}

//t_list	*ft_lstlast(t_list *lst)
//{
//	if (lst)
//	{
//		while (lst->next != NULL)
//		{
//			lst = lst->next;
//		}
//	}
//	return (lst);
//}

//int	main(void)
//{
//	t_list	*a;
//	t_list	*b;
//	t_list	*last;

//	a = create_node(1);
//	a->next =  create_node(2);
//	a->next->next = create_node(3);
//	a->next->next->next = create_node(0);
//	b = create_node(7);
//	last = ft_lstlast(a);
//	printf("Original last node = %d", last->content);
//	printf("\n");
//ft_lstadd_back(&a, b);
//	last = ft_lstlast(a);
//	printf("New last node = %d", last->content);
//	printf("\n");
//	return (0);
//}

void	ft_lstadd_back(t_list **lst, t_list *new)
{
	t_list	*last;

	if (lst == NULL)
		return ;
	if (*lst == NULL)
	{
		*lst = new;
		return ;
	}
	last = ft_lstlast(*lst);
	last->next = new;
}
