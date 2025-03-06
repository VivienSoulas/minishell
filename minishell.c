/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vsoulas <vsoulas@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/27 11:09:10 by vsoulas           #+#    #+#             */
/*   Updated: 2025/03/06 09:54:07 by vsoulas          ###   ########.fr       */
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
		free(input);
	}
	ft_free_list(&token);
	return (0);
}

int	ft_parse_input(char *in, char **env, int *exit_stat, t_token **token)
{
	char	**tokens;
	int		args;

	tokens = ft_split(in, ' ');
	if (tokens == NULL)
		return (*exit_stat);
	args = ft_count_args(tokens);
	if (args == 1)
		*exit_stat = ft_handle_one(in, env);
	else
		*exit_stat = ft_tokenise(tokens, token);
	ft_free_split(tokens);
	return (*exit_stat);
}

// handle pwd better by looking for pwd and return good output
int	ft_handle_one(char *input, char **env)
{
	int	i;

	if (ft_strncmp(input, "pwd", 3) == 0)
	{
		write(1, &env[6][7], ft_strlen(env[6]) - 7);
		write(1, "\n", 1);
	}
	else if (ft_strncmp(input, "env", 3) == 0)
	{
		i = 0;
		while (env[i])
		{
			printf("%s\n", env[i]);
			i++;
		}
	}
	else if (ft_strncmp(input, "exit", 5) == 0)
		return (1);
	return (0);
}

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
