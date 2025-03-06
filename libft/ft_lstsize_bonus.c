/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstsize_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vsoulas <vsoulas@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/25 13:46:52 by vsoulas           #+#    #+#             */
/*   Updated: 2024/10/28 09:56:09 by vsoulas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// count the number of nodes in a list

#include "libft.h"

//#include <stdio.h>
//#include <stdlib.h>

//typedef struct s_list
//{
//	int content;
//    struct s_list *next;
//} t_list;

//int	ft_lstsize(t_list *lst);
//t_list	*create_node(int value);

//int	main(void)
//{
//	t_list	*a;
//	int		size;

//	a = create_node(0);
//	a->next =  create_node(1);
//	a->next->next = create_node(2);
//	size = ft_lstsize(a);
//	printf("%i\n", size);
//	return (0);
//}

//t_list	*create_node(int value)
//{
//    t_list *new_node = malloc(sizeof(t_list));
//    if (!new_node)
//        return NULL;
//    new_node->content = value;
//    new_node->next = NULL;
//    return (new_node);
//}

int	ft_lstsize(t_list *lst)
{
	int	count;

	count = 0;
	if (lst)
	{
		while (lst != NULL)
		{
			count++;
			lst = lst->next;
		}
	}
	return (count);
}
