/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vsoulas <vsoulas@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/28 09:55:25 by vsoulas           #+#    #+#             */
/*   Updated: 2024/10/28 16:22:35 by vsoulas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*Iterates the list ’lst’ and applies the function
’f’ on the content of each node. Creates a new
list resulting of the successive applications of
the function ’f’. The ’del’ function is used to
delete the content of a node if needed.*/

#include "libft.h"

// #include <stdio.h>
// #include <stdlib.h>

// typedef struct s_list
// {
// 	int				*content;
// 	struct s_list	*next;
// }	t_list;

// t_list	*ft_lstmap(t_list *lst, void *(*f)(void *),void (*del)(void *));

// t_list	*create_list(void *content)
// {
// 	t_list	*node;
// 	node = malloc (sizeof(t_list));
// 	if (!node)
// 		return (NULL);
// 	node->content = content;
// 	node->next = NULL;
// 	return (node);
// }

// void	*f(void *content)
// {
// 	t_list	*node;
// 	int		*i;
// 	int		a;

// 	a = 666;
// 	i = &a;
// 	content = i;
// 	return (content);
// }

// void	del(void *content)
// {
// // if we want to free
// 	// free(content);
// // if we want to check set to 0 orherwise cant printf
// 	*(int *)content = 0;
// }

// int	main(void)
// {
// 	t_list	*lst;
// 	t_list	*node;
// 	t_list	*node1;
// 	t_list	*new_list;
// 	t_list	*new_node;
// 	t_list	*new_node1;
// 	int		*i;
// 	int		*j;
// 	int		*k;
// 	int		a;
// 	int		b;
// 	int		c;

// 	a = 5;
// 	i = &a;
// 	b = 10;
// 	j = &b;
// 	c = 45;
// 	k = &c;
// 	lst = ft_lstnew(i);
// 	lst->next = ft_lstnew(j);
// 	lst->next->next = ft_lstnew(k);
// 	node = lst->next;
// 	node1 = lst->next->next;
// 	printf("before %i, %i, %i\n", *(int *)(lst->content),
	// *(int *)(node->content), *(int *)(node1->content));
// 	new_list = ft_lstmap(lst, f, del);
// 	new_node = new_list->next;
// 	new_node1 = new_list->next->next;
// 	printf("after %i, %i, %i\n", *(int *)(new_list->content),
// *(int *)(new_node->content), *(int *)(new_node1->content));
// 	return (0);
// }

t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list	*new_lst;
	t_list	*new_node;
	void	*new_content;

	new_lst = NULL;
	while (lst)
	{
		new_content = f(lst->content);
		if (!new_content)
		{
			ft_lstclear(&new_lst, del);
			return (NULL);
		}
		new_node = ft_lstnew(new_content);
		if (!new_node)
		{
			del(new_content);
			ft_lstclear(&new_lst, del);
			return (NULL);
		}
		ft_lstadd_back(&new_lst, new_node);
		lst = lst->next;
	}
	return (new_lst);
}
