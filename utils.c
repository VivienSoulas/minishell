/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vsoulas <vsoulas@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/10 12:01:39 by vsoulas           #+#    #+#             */
/*   Updated: 2025/07/18 13:00:45 by vsoulas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

int	ft_count_args(char **tokens)
{
	int	i;

	i = 0;
	while (tokens[i])
		i++;
	return (i);
}

char	*ft_strjoin_free(char *s1, char *s2)
{
	char	*new_str;
	int		len1;
	int		len2;

	if (s1 == NULL || s2 == NULL)
		return (NULL);
	len1 = ft_strlen(s1);
	len2 = ft_strlen(s2);
	new_str = malloc(sizeof(char) * (len1 + len2 + 1));
	if (new_str == NULL)
		return (free(s1), error(3, NULL), NULL);
	ft_memcpy(new_str, s1, len1);
	ft_memcpy(new_str + len1, s2, len2);
	new_str[len1 + len2] = '\0';
	free(s1);
	return (new_str);
}

int	ft_initialise_expansion(t_expansion *exp, char **env)
{
	exp->state = 0;
	exp->i = 0;
	exp->exit_stat = 0;
	exp->exit = 0;
	exp->initial_stdout = -1;
	exp->initial_stdin = -1;
	exp->env = copy_envp(env);
	if (exp->env == NULL)
		return (ft_free_envp_list(&exp->env), exp->exit_stat = 1);
	exp->export = copy_export(env);
	if (exp->export == NULL)
	{
		ft_free_export_list(&exp->export);
		return (ft_free_envp_list(&exp->env), exp->exit_stat = 1);
	}
	exp->envp = list_to_array(&exp->env);
	if (!exp->envp)
	{
		free_array(exp->envp);
		ft_free_envp_list(&exp->env);
		ft_free_export_list(&exp->export);
		return (exp->exit_stat = 1);
	}
	return (0);
}

int	command_count(t_command **commands)
{
	int	res;

	res = 0;
	if (commands == NULL)
		return (res);
	while (commands[res])
	{
		res++;
	}
	return (res);
}
