/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vsoulas <vsoulas@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/10 15:55:51 by vsoulas           #+#    #+#             */
/*   Updated: 2025/07/10 16:52:51 by vsoulas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	forceout(void)
{
	return (0);
}

void	parent(int sig)
{
	if (sig == SIGINT)
	{
		rl_replace_line("", 0);
		rl_on_new_line();
		printf("\n");
		rl_redisplay();
	}
}

void	child(int sig)
{
	if (sig == SIGINT)
	{
		rl_replace_line("", 0);
		rl_on_new_line();
	}
}

void	heredoc(int sig)
{
	if (sig == SIGINT)
	{
		rl_replace_line("", 0);
		rl_on_new_line();
		g_heredoc_variable = 1;
		rl_done = 1;
	}
}

void	sig_hand(int sig)
{
	if (sig == MAIN)
	{
		signal(SIGINT, &parent);
		signal(SIGQUIT, SIG_IGN);
	}
	if (sig == CHILD)
	{
		signal(SIGINT, &child);
		signal(SIGQUIT, SIG_IGN);
	}
	if (sig == HEREDOC)
	{
		signal(SIGINT, &heredoc);
		signal(SIGQUIT, SIG_IGN);
	}
}
