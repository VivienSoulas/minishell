/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstclear_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vsoulas <vsoulas@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/28 09:55:47 by vsoulas           #+#    #+#             */
/*   Updated: 2024/10/28 09:55:48 by vsoulas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*Deletes and frees the given node and every
successor of that node, using the function ’del’
and free(3).
Finally, the pointer to the list must be set to
NULL.*/

#include "libft.h"

// #include <stdio.h>
// #include <stdlib.h>

// typedef struct s_list
// {
// 	int				*content;
// 	struct s_list	*next;
// }	t_list;

// // void	ft_lstclear(t_list **lst, void (*del)(void*));
// // void	del(void *data);

// t_list	*create_new_list(int *i)
// {
// 	t_list	*node;

// 	node = malloc (sizeof(t_list));
// 	if (!node)
// 		return (NULL);
// 	node->content = i;
// 	node->next = NULL;
// 	return (node);
// }

// void	del(void *data)
// {
//  // to actually free the memory
// 	// free(data);
// // to checkthe change, only change to 0 so i can printf
// 	*(int *)data = 0;
// }

// int	main(void)
// {
// 	t_list	*lst;
// 	t_list	*lst1;
// 	t_list	*lst2;
// 	int		*j;
// 	int		*k;
// 	int		*l;
// 	int		i;
// 	int		m;
// 	int		n;

// 	i = 5;
// 	j = &i;
// 	m = 10;
// 	k = &m;
// 	n = 15;
// 	l = &n;
// 	lst = create_new_list(j);
// 	lst1 = create_new_list(k);
// 	lst2 = create_new_list(l);
// 	lst->next = lst1;
// 	lst1->next = lst2;
// 	printf("lst = %i, lst1 = %i, lst2 =%i\n",
// *(lst->content), *(lst1->content), *(lst2->content));
// 	printf("lst->next = %i, lst1->next = %i,
// lst2->next =%i\n", lst->next, lst1->next, lst2->next);
// 	ft_lstclear(&lst, del);
// 	printf("lst = %i, lst1 = %i, lst2 =%i\n", 
// *(lst->content), *(lst1->content), *(lst2->content));
// 	printf("lst->next = %i, lst1->next = %i,
//  lst2->next =%i\n", lst->next, lst1->next, lst2->next);
// 	return (0);
// }

// comment out *lst = NULL; to try out the code without error;
void	ft_lstclear(t_list **lst, void (*del)(void *))
{
	t_list	*current;
	t_list	*temp;

	current = *lst;
	if (!lst || !del)
		return ;
	while (current != NULL)
	{
		temp = current;
		current = current->next;
		del(temp->content);
		free(temp);
	}
	*lst = NULL;
}
