/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstadd_front_bonus.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vsoulas <vsoulas@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/25 11:31:10 by vsoulas           #+#    #+#             */
/*   Updated: 2024/10/28 09:55:42 by vsoulas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// Adds the node ’new’ at the beginning of the list

#include "libft.h"

// t_list	*ft_lstnew(void *content);
// void	ft_lstadd_front(t_list **lst, t_list *new);

// int	main(void)
// {
// 	t_list	*start;
// 	t_list	*node;
// 	t_list	*node1;
// 	int		content;
// 	int 	content1;
// 	int		content2;
// 	int		*x;
// 	int		*x1;
// 	int		*x2;
// 	int		*x3;

// 	content = 0;
// 	start = ft_lstnew(&content);
// 	content1 = 1;
// 	node = ft_lstnew(&content1);
// 	content2 = 2;
// 	node1 = ft_lstnew(&content2);
// 	x = (int *)start->content;
// 	x1 = (int *)node->content;
// 	x2 = (int *)node1->content;
// 	printf("start = %d\n", *x);
// 	printf("node = %d\n", *x1);
// 	printf("node1 = %d\n", *x2);
// 	ft_lstadd_front(&start, node);
// 	x3 = (int *)start->content;
// 	printf("after : start = %d\n", *x3);
// }

void	ft_lstadd_front(t_list **lst, t_list *new)
{
	if (lst && new)
	{
		new->next = *lst;
		*lst = new;
	}
}
