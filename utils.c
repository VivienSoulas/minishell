/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vsoulas <vsoulas@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/10 12:01:39 by vsoulas           #+#    #+#             */
/*   Updated: 2025/04/10 12:01:40 by vsoulas          ###   ########.fr       */
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

void	handler(int sig)
{
	(void)sig;
	printf("\n");
	g_signal_caught = 1;
	rl_on_new_line();
	rl_replace_line("", 0);
	rl_redisplay();
}

void	signals_handling(void)
{
	signal(SIGQUIT, SIG_IGN);
	signal(SIGINT, &handler);
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

void	ft_initialise_expansion(t_expansion *exp, t_envp **env, int *exit)
{
	exp->state = 0;
	exp->i = 0;
	exp->exit = exit;
	exp->env = env;
}
