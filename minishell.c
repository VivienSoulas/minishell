/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vsoulas <vsoulas@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/27 11:09:10 by vsoulas           #+#    #+#             */
/*   Updated: 2025/03/06 15:19:36 by vsoulas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/* STEPS */
// go through the input and split in order to find the different tokens
// check tokens to find operators, input, output, args, redirections etc
// assign each token to different type and redirect them to exec
//
// special cases: "", '', >, >>, <,  << $, $?, |
// ◦ echo with option -n
// ◦ cd with only a relative or absolute path
/* ◦ pwd with no options */
// ◦ export with no options
// ◦ unset with no options
/* ◦ env with no options or arguments */
// ◦ exit with no options
//
// error on \, ;
// single quote in order to keep special symboles as their original meanings
// double quote to keep meaning of all char in the quote except $(...)
// $(...) == replace it by a specifique string stated ahead
// <infile grep '$USER':"$USER"|wc -l>outfile
#include "parsing.h"

int	main(int ac, char **av, char **envp)
{
	char	*input;
	int		exit_status;
	t_token	*token;

	(void)av;
	token = NULL;
	exit_status = 0;
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
		ft_parse_input(input, envp, &exit_status, &token);
// exec call
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

	tokens = ft_split(in, ' ');
	if (tokens == NULL)
		return (*exit_stat);
	*exit_stat = ft_tokenise(tokens, token);
	*exit_stat = ft_check_token(*token, env);
	return (*exit_stat);
}

// create a linked list with each parts of the command (aka tokens)
int	ft_tokenise(char **tokens, t_token **token)
{
	int		i;
	t_token	*node;

	i = 0;
	while (tokens[i])
	{
		node = ft_new_node(tokens[i]);
		if (node == NULL)
			return (1);
		ft_add_last(token, node);
		i++;
	}
	return (0);
}

// check each token to asign it with the good code number
// check for forbidden / and ;
// _____________________________________________________
// /!\ TO DO /!\
// check for " and ' (also check for unclosed quotes)
// check for $?
int	ft_check_token(t_token *token, char **env)
{
	//t_dollar	*dollar;

	//dollar = NULL;
	while (token)
	{
		if (ft_strncmp(token->input, "env", 3) == 0
			|| ft_strncmp(token->input, "pwd", 3) == 0
			|| ft_strncmp(token->input, "exit", 5) == 0)
			{
				if (ft_handle_one(token->input, env) == 1)
				return (1);
			}
		else if (ft_strncmp(token->input, "|", 1) == 0)
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
			|| ft_strncmp(token->input, ";", 1) == 0)
			return (0);
		else
			token->type = 6;
		token = token->next;
	}
	//if (dollar->value != NULL)
	//	free(dollar->value);
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
