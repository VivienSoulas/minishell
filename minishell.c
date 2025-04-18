/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vsoulas <vsoulas@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/27 11:09:10 by vsoulas           #+#    #+#             */
/*   Updated: 2025/04/18 14:32:21 by vsoulas          ###   ########.fr       */
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
	int			exit_call;
	int			exit_status;
	t_envp		*env_list;
	t_token		*token;

	(void)av;
	if (ac != 1)
		return (EXIT_FAILURE);
	env_list = copy_envp(envp);
	if (env_list == NULL)
		return (ft_free_envp_list(&env_list), EXIT_FAILURE);
	token = NULL;
	exit_call = 0;
	exit_status = 0;
	signals_handling();
	while (exit_call == 0)
	{
		ft_loop(&exit_status, &token, &env_list, &exit_call);
	}
	return (ft_free_envp_list(&env_list), exit_status);
}

// loop that repeats itself until exit call = 1
// (aka malloc fail or exit prompted)
int	ft_loop(int *exit_stat, t_token **token, t_envp **env, int *exit_c)
{
	char		*input;
	t_command	**commands;

	if (g_signal_caught == 1)
		g_signal_caught = 0;
	input = readline("minishell> ");
	if (input == NULL)
		return (*exit_c = 1);
	add_history(input);
	if (ft_parse_input(input, exit_c, token) != 1)
	{
		if (ft_strncmp((*token)->input, "export", 7) == 0
			&& ft_export_check(env, token, exit_stat) == 1)
			return (free(input), ft_free_list(token), *exit_c = 1);
		commands = token_to_cmd(token, env);
		*exit_stat = exe_cmds(commands, env, exit_c, token);
		command_cleanup(commands);
	}
	return (free(input), ft_free_list(token), 0);
}

/* split doesnt work for finding all args
because not all args are separated by white space
example : <infile grep '$USER' "$USER"|wc -l>outfile */
int	ft_parse_input(char *in, int *exit, t_token **token)
{
	char		**tokens;
	t_split		*split;

	if (in == NULL || in[0] == '\0')
		return (1);
	if (ft_check_quotes(in) == 1)
		return (1);
	split = malloc(sizeof(t_split));
	if (split == NULL)
		return (error(3, NULL), *exit = 1);
	if (ft_initialise_split(split, in) == 1)
		return (free(split), *exit = 1);
	tokens = ft_split_input(in, split, exit);
	if (tokens == NULL && *exit == 1)
		return (free(split), *exit = 1);
	else if (tokens == NULL)
		return (free(split), 0);
	if (ft_list_tokens(tokens, token) == 1)
		return (ft_free_split(tokens), free(split), *exit = 1);
	ft_assign_types(*token);
	if (ft_check_tokens(token) == 1)
		return (error(1, NULL), ft_free_split(tokens), free(split), 1);
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
