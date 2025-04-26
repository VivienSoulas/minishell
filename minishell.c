/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vsoulas <vsoulas@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/27 11:09:10 by vsoulas           #+#    #+#             */
/*   Updated: 2025/04/18 16:02:10 by vsoulas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/* STEPS */
// go through the input and split in order to find the different tokens
// check tokens to find operators, input, output, args, redirections etc
// assign each token to different type and redirect them to exec
#include "parsing.h"

volatile sig_atomic_t	g_signal_caught = 0;

int	main(int ac, char **av, char **envp)
{
	int			exit_status;
	t_expansion	*e;
	t_token		*token;

	e = malloc(sizeof(t_expansion));
	if (e == NULL)
		return (EXIT_FAILURE);
	if (ft_initialise_expansion(e, envp) == 1)
		return (ft_free_e(&e), EXIT_FAILURE);
	(void)av;
	if (ac != 1)
		return (ft_free_e(&e), EXIT_FAILURE);
	token = NULL;
	signals_handling();
	while (e->exit == 0)
	{
		ft_loop(&token, e);
	}
	exit_status = e->exit_stat;
	return (ft_free_e(&e), exit_status);
}

// loop that repeats itself until exit call = 1
// (aka malloc fail or exit prompted)
int	ft_loop(t_token **token, t_expansion *e)
{
	char		*input;
	t_command	**commands;

	if (g_signal_caught == 1)
		g_signal_caught = 0;
	input = readline("\033[38;2;0;255;0mminishell> \033[0m");
	if (input == NULL)
		return (e->exit = 1);
	add_history(input);
	if (ft_parse_input(input, e, token) != 1)
	{
		if (ft_strncmp((*token)->input, "export", 7) == 0)
		{
			if (ft_export_check(token, e) == 1)
				return (free(input), ft_free_list(token), e->exit = 1);
		}
		else
		{
			commands = token_to_cmd(token, &e->env);
			e->exit_stat = exe_cmds(commands, e, token);
			command_cleanup(commands);
		}
	}
	return (free(input), ft_free_list(token), 0);
}

/* split doesnt work for finding all args
because not all args are separated by white space
example : <infile grep '$USER' "$USER"|wc -l>outfile */
int	ft_parse_input(char *in, t_expansion *e, t_token **token)
{
	char		**tokens;
	t_split		*split;

	if (in == NULL || in[0] == '\0')
		return (e->exit_stat = 1);
	if (ft_check_quotes(in) == 1)
		return (e->exit_stat = 1);
	split = malloc(sizeof(t_split));
	if (split == NULL)
		return (error(3, NULL), e->exit = 1);
	if (ft_initialise_split(split, in) == 1)
		return (free(split), e->exit = 1);
	tokens = ft_split_input(in, split, e->exit);
	if (tokens == NULL && e->exit == 1)
		return (free(split), 1);
	else if (tokens == NULL)
		return (free(split), 0);
	if (ft_list_tokens(tokens, token) == 1)
		return (ft_free_split(tokens), free(split), e->exit = 1);
	if (ft_variable_expansion(*token, e) == 1)
		return (ft_free_split(tokens), free(split), e->exit = 1);
	ft_assign_types(*token);
// t_token *current;
// current = *token;
// while (current)
// {
// 	printf("%s.\ntype%i\n", current->input, current->type);
// 	current = current->next;
// }
	if (ft_check_tokens(token) == 1)
		return (error(1, NULL), ft_free_split(tokens), free(split), e->exit_stat = 127);
	return (ft_free_split(tokens), free(split), 0);
}

void	ft_assign_types(t_token *token)
{
	t_token	*current;
	int		is_cmd_context;
	int		is_redirection;

	is_cmd_context = 0;
	is_redirection = 0;
	current = token;
	if (token == NULL)
		return ;
	while (current)
	{
		if (assign_pipe(current, &is_cmd_context, &is_redirection))
			;
		else if (assign_redirection(current, &is_redirection))
			;
		else if (assign_file(current, &is_redirection))
			;
		else if (assign_cmd_or_arg(current, &is_cmd_context, &is_redirection))
			;
		current = current->next;
	}
}

int	ft_check_tokens(t_token **token)
{
	t_token	*node;

	node = *token;
	if (node == NULL)
		return (1);
	if (ft_pipe_check(token) == 1)
		return (1);
	while (node && node->next)
	{
		if (node->type == FORBIDDEN)
			return (1);
		if (((node->type >= 1 && node->type <= 5)
				&& (node->next->type >= 1 && node->next->type <= 5))
			|| (node->type == 1 && node->next->type == 1))
			return (1);
		node = node->next;
	}
	if (node->next == NULL && (node->type >= 1 && node->type <= 5))
		return (1);
	return (0);
}
