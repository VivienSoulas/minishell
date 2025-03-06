/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstdelone_bonus.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vsoulas <vsoulas@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/25 16:37:33 by vsoulas           #+#    #+#             */
/*   Updated: 2024/10/28 09:55:50 by vsoulas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*	Takes as a parameter a node and frees the memory of
	the node’s content using the function ’del’ given
	as a parameter and free the node. The memory of
	’next’ must not be freed.*/

#include "libft.h"

// #include <stdio.h>
// #include <stdlib.h>

// typedef struct s_list
// {
//    int 			 	*content;
//    struct s_list	*next;
// } t_list;

// void	ft_lstdelone(t_list *lst, void (*del)(void*));
// void	del(void *data);

// t_list	*creat_lst(int *i)
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
// 	int		i;
// 	int		*j;

// 	i = 5;
// 	j = &i;
// 	lst = creat_lst(j);
// 	printf("before %i\n", *(lst->content));
// 	ft_lstdelone(lst, &del);
// 	printf("after %i\n", *(lst->content));
// 	return (0);
// }

void	ft_lstdelone(t_list *lst, void (*del)(void*))
{
	if (!lst || !del)
		return ;
	del(lst->content);
	free(lst);
}
