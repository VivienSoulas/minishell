/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vsoulas <vsoulas@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/27 11:09:10 by vsoulas           #+#    #+#             */
/*   Updated: 2025/03/13 14:55:57 by vsoulas          ###   ########.fr       */
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

volatile sig_atomic_t g_signal_caught = 0;

int	main(int ac, char **av, char **envp)
{
	char	*input;
	int		exit_status;
	t_token	*token;

	(void)av;
	token = NULL;
	exit_status = 0;
signals_handling();
	if (ac != 1)
		return (EXIT_FAILURE);
	while (exit_status == 0)
	{
		input = readline("minishell> ");
		if (input == NULL)
		{
			printf("Error: couldn't read input\n");
			return (EXIT_FAILURE);
		}
		add_history(input);
		if (ft_parse_input(input, envp, &exit_status, &token) != 2)
			exit_status = ft_temp_exec(&token, envp);
// exec call
print_token_list(&token);
		free(input);
		ft_free_list(&token);
	}
	return (0);
}

/* split doesnt work for finding all args
because not all args are separated by white space
example : <infile grep '$USER':"$USER"|wc -l>outfile */
int	ft_parse_input(char *in, char **env, int *exit_stat, t_token **token)
{
	char		**tokens;
	t_split		*split;

	(void)env;
	if (in == NULL || in[0] == '\0')
		return (1);
	split = malloc(sizeof(t_split));
	if (split == NULL)
		return (*exit_stat = 1);
	if (ft_initialise_split(split, in) == 1)
		return (free(split), *exit_stat = 1);
	tokens = ft_split_input(in, split);
	if (tokens == NULL)
		return (free(split), *exit_stat = 1);
	*exit_stat = ft_list_tokens(tokens, token);
	ft_assign_types(*token);
	if (ft_check_tokens(token) == 1)
	{
		printf("Invalid input\n");
		return (ft_free_split(tokens), free(split), 2);
	}
// check token for $ and replace
	ft_free_split(tokens);
	return (free(split), *exit_stat);
}

// check each token to asign it with the good code number
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
		else if (ft_strncmp(token->input, "echo", 5) == 0)
			token->type = 7;
		else if (ft_strncmp(token->input, "/", 1) == 0
			|| ft_strncmp(token->input, ";", 1) == 0
			|| ft_strncmp(token->input, ":", 1) == 0)
			token->type = 8;
		else
			token->type = 6;
		token = token->next;
	}
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
	if (node && node->type != 6)
		return (1);
	return (0);
}

//// finds the ARG to replace after $
//int	ft_dollar_asign(t_token *token, t_dollar *dollar)
//{
//	int		i;
//	int		len;

//	len = ft_strlen(token->input) - 5;
//	dollar->value = malloc(sizeof(char) * (len + 1));
//	if (dollar->value == NULL)
//		return (1);
//	i = 0;
//	while (i < len)
//	{
//		dollar->value[i] = token->input[i + 5];
//		i++;
//	}
//	dollar->value[i] = '\0';
//	return (0);
//}

//int	ft_fill_arg(t_token *token, t_dollar *dollar)
//{
//	free(token->input);
//	token->input = strdup(dollar->value);
//	if (token->input == NULL)
//		return (1);
//	return (0);
//}
