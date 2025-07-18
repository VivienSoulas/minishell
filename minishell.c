/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdavtian <jdavtian@student.codam.nl>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/27 11:09:10 by vsoulas           #+#    #+#             */
/*   Updated: 2025/07/18 14:28:43 by jdavtian         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/* STEPS */
// go through the input and split in order to find the different tokens
// check tokens to find operators, input, output, args, redirections etc
// assign each token to different type and redirect them to exec
#include "parsing.h"

sig_atomic_t	g_heredoc_variable = 0;

int	main(int ac, char **av, char **envp)
{
	t_expansion	*e;
	t_token		*token;

	(void)av;
	if (ac != 1)
		return (EXIT_FAILURE);
	e = malloc(sizeof(t_expansion));
	if (e == NULL)
		return (EXIT_FAILURE);
	ft_memset(e, 0, sizeof(t_expansion));
	if (ft_initialise_expansion(e, envp) == 1)
		return (ft_free_e(&e), EXIT_FAILURE);
	token = NULL;
	sig_hand(MAIN);
	while (e->exit == 0)
	{
		ft_loop(&token, e);
	}
	if (e->exit != 0)
		printf("exit\n");
	return (ft_free_e(&e), ft_free_list(&token), 0);
}

// loop that repeats itself until exit call = 1
// (aka malloc fail or exit prompted)
int	ft_loop(t_token **token, t_expansion *e)
{
	char		*input;

	sig_hand(MAIN);
	if (g_heredoc_variable == 1)
	{
		e->exit_stat = 130;
		g_heredoc_variable = 0;
	}
	input = readline("\033[38;2;0;255;0mminishell> \033[0m");
	if (input == NULL)
		return (e->exit = 1);
	add_history(input);
	if (ft_parse_input(input, e, token) != 1)
	{
		if (ft_exe(token, e) == 1)
			return (e->exit = 1);
	}
	return (ft_free_list(token), free(input), 0);
}

int	ft_exe(t_token **token, t_expansion *e)
{
	if (token_to_cmd(token, e) == NULL)
		return (command_cleanup(&e->cmd),
			ft_free_list(token), e->exit_stat = 1, 0);
	e->exit_stat = exe_cmds(e->cmd, e, token);
	command_cleanup(&e->cmd);
	e->cmd = NULL;
	return (0);
}
