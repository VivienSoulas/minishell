/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vsoulas <vsoulas@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/27 11:09:10 by vsoulas           #+#    #+#             */
/*   Updated: 2025/03/21 15:58:45 by vsoulas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// test_input
// $ARG="12 34" <infile grep    '$US<ER' "$USER"|wc  -l>outfile <<append                >>append echo -n "hello world   this" expdand $ARG dont_expand '$ARG' expand "$ARG"
//
/* STEPS */
// go through the input and split in order to find the different tokens
// check tokens to find operators, input, output, args, redirections etc
// assign each token to different type and redirect them to exec
#include "parsing.h"

volatile sig_atomic_t	g_signal_caught = 0;

int	main(int ac, char **av, char **envp)
{
	char		*input;
	int			exit_call;
	int			exit_status;
	t_token		*token;
	t_command	**commands;
	t_envp		*env_list;

	(void)av;
	if (ac != 1)
		return (EXIT_FAILURE);
	env_list = copy_envp(envp);
	token = NULL;
	exit_call = 0;
	signals_handling();
	while (exit_call == 0)
	{
		if (g_signal_caught == 1)
			g_signal_caught = 0;
		input = readline("minishell> ");
		if (input == NULL)
			return (ft_free_envp_list(&env_list), EXIT_FAILURE);
		add_history(input);
		if (ft_parse_input(input, &env_list, &exit_call, &token) != 1)
		{
		//	exit_call = ft_temp_exec(&token, &env_list);
		//}
		commands = token_to_cmd(&token);
		exit_status = exec_list_command(commands);
		}
		command_cleanup(commands);
		free(input);
		ft_free_list(&token);
	}
	return (ft_free_envp_list(&env_list), 0);
}

/* split doesnt work for finding all args
because not all args are separated by white space
example : <infile grep '$USER' "$USER"|wc -l>outfile */
int	ft_parse_input(char *in, t_envp **env, int *exit, t_token **token)
{
	char		**tokens;
	t_split		*split;

	if (in == NULL || in[0] == '\0')
		return (1);
	split = malloc(sizeof(t_split));
	if (split == NULL)
		return (ft_mem_error(), *exit = 1);
	if (ft_initialise_split(split, in) == 1)
		return (free(split), ft_mem_error(), *exit = 1);
	tokens = ft_split_input(in, split);
	if (tokens == NULL)
		return (free(split), ft_mem_error(), *exit = 1);
	*exit = ft_list_tokens(tokens, token);
	ft_assign_types(*token);
	if (ft_variable_expansion(token, env, exit) == 1)
		return (ft_free_split(tokens), free(split), ft_mem_error(), *exit = 1);
	if (ft_check_tokens(token) == 1)
	{
		printf("Invalid input\n");
		return (ft_free_split(tokens), free(split), 1);
	}
	ft_free_split(tokens);
	return (free(split), 0);
}

// check each token to asign it with the good code number
// check for forbidden / and ;
// _____________________________________________________
// ◦ echo with option -n
// ◦ cd with only a relative or absolute path
/* ◦ pwd with no options */
// ◦ export with no options
// ◦ unset with no options
/* ◦ env with no options or arguments */
/* ◦ exit with no options */
void	ft_assign_types(t_token *token)
{
	while (token)
	{
		if (ft_strncmp(token->input, "|", 1) == 0)
			token->type = 1;
		else if (ft_strncmp(token->input, "<<", 2) == 0)
			token->type = 4;
		else if (ft_strncmp(token->input, ">>", 2) == 0)
			token->type = 5;
		else if (ft_strncmp(token->input, "<", 1) == 0)
			token->type = 2;
		else if (ft_strncmp(token->input, ">", 1) == 0)
			token->type = 3;
		else if (ft_strncmp(token->input, "/", 1) == 0
			|| ft_strncmp(token->input, ";", 1) == 0
			|| ft_strncmp(token->input, ":", 1) == 0)
			token->type = 7;
		else
			token->type = 6;
		token = token->next;
	}
}

int	ft_variable_expansion(t_token **token, t_envp **env, int *exit)
{
	t_token	*current;

	current = *token;
	while (current)
	{
		if (ft_strncmp(current->input, "$", 1) == 0)
		{
			if (ft_strncmp(current->input + 1, "?", 1) == 0)
				ft_print_exit_status(exit);
			else if (ft_dollar_sign(current, env) != 0)
				return (1);
		}
		if (ft_strncmp(current->input, "\"", 1) == 0)
		{
			if (ft_double_quote_expand(current, env) != 0)
				return (1);
		}
		if (ft_strncmp(current->input, "\'", 1) == 0)
		{
			if (ft_single_quote_expand(current, env) != 0)
				return (1);
		}
		current = current->next;
	}
	return (0);
}

// check for consecutive operators
// check for operators at the end of input
// check for forbidden operators (type 8)
int	ft_check_tokens(t_token **token)
{
	t_token	*node;

	node = *token;
	if (node->type == 1)
		return (1);
	while (node && node->next)
	{
		if ((node->type != 6 && node->next->type != 6) || node->type == 8)
			return (1);
		node = node->next;
	}
	if (node->type != 6)
		return (1);
	return (0);
}
