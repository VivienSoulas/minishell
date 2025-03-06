/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstnew_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vsoulas <vsoulas@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/25 11:08:48 by vsoulas           #+#    #+#             */
/*   Updated: 2024/10/28 09:56:06 by vsoulas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// create a new node and fill it with content

#include "libft.h"

// t_list	*ft_lstnew(void *content);

//int	main(void)
//{
//	t_list	*node;
//	int		content;
//	int		*x;

//	content = 5;
//	node = ft_lstnew(&content);
//	x = (int *)node->content;
//	printf("new node content = %d, next = %p\n", *x, node->next);
//	free(node);
//	return (0);
//}

t_list	*ft_lstnew(void *content)
{
	t_list	*node;

	node = malloc (sizeof(t_list));
	if (!node)
		return (NULL);
	node->content = content;
	node->next = NULL;
	return (node);
}
