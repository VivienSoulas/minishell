/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cpy_env.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vsoulas <vsoulas@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/21 13:17:37 by jdavtian          #+#    #+#             */
/*   Updated: 2025/03/21 14:12:40 by vsoulas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

char	*copy_str_delimiter(char *str, int check)
{
	char	*res;
	char	*equal;

	equal = ft_strchr(str, '=');
	if (check)
	{
		res = malloc(equal - str + 1);
		if (!res)
			return (NULL);
		ft_strlcpy(res, str, equal - str + 1);
		return (res);
	}
	else
	{
		res = malloc(ft_strlen(equal + 1) + 1);
		if (!res)
			return (NULL);
		ft_strlcpy(res, equal + 1, ft_strlen(equal + 1) + 1);
		return (res);
	}
	return (NULL);
}

t_envp	*new_envp(char *envp)
{
	t_envp *new;

	new = malloc(sizeof(t_envp));
	if (new == NULL)
	{
		printf("Malloc failed\n");
		return (NULL);
	}
	new->name = copy_str_delimiter(envp, 1);
	new->value = copy_str_delimiter(envp, 0);
	new->next = NULL;
	return (new);
}

void	add_to_envp(t_envp **envp_list, char *envp)
{
	t_envp	*temp;
	t_envp	*new;

	if (*envp_list == NULL)
	{
		*envp_list = new_envp(envp);
		return ;
	}
	temp = *envp_list;
	while(temp->next)
		temp = temp->next;
	new = new_envp(envp);
	temp->next = new;
}

t_envp	*copy_envp(char **envp)
{
	t_envp *envp_list;
	int		i;

	i = 0;
	envp_list = NULL;
	while (envp[i])
	{
		add_to_envp(&envp_list, envp[i]);
		i++;
	}
	return (envp_list);
}

// int	main(int argc, char **argv, char **envp)
// {
// 	t_envp *envp_list = copy_envp(envp);

// 	while (envp_list->next)
// 	{
// 		printf("%s=%s\n", envp_list->name, envp_list->value);
// 		envp_list = envp_list->next;
// 	}
// 	return (0);
// }