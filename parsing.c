/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_parsing.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vsoulas <vsoulas@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/18 12:28:03 by vsoulas           #+#    #+#             */
/*   Updated: 2025/05/30 12:21:57 by vsoulas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_parse_input(char *in, t_expansion *e, t_token **token)
{
	char		**tokens;
	t_split		*split;

	if (in == NULL || in[0] == '\0' || (in[0] >= 7 && in[0] <= 13)
		|| in[0] == ' ')
		return (e->exit_stat = 1);
	if (ft_check_quotes(in) == 1)
		return (e->exit_stat = 1);
	split = malloc(sizeof(t_split));
	if (split == NULL)
		return (error(3, NULL), e->exit = 1);
	if (ft_initialise_split(split, in) == 1)
		return (free(split), e->exit = 1);
	tokens = ft_split_input(in, split, e);
	if (tokens == NULL && e->exit == 1)
		return (free(split), 1);
	else if (tokens == NULL)
		return (free(split), 0);
	if (ft_list_tokens(tokens, token) == 1)
		return (free_array(tokens), free(split), e->exit = 1);
	if (ft_variable(token, e) == 1)
		return (free_array(tokens), free(split), e->exit = 1);
	if (ft_check_tokens(token, e) == 1)
		return (error(1, NULL), free_array(tokens), free(split), 1);
	return (free_array(tokens), free(split), 0);
}

int	ft_variable(t_token **token, t_expansion *e)
{
	t_token	*current;

	current = *token;
	while (current)
	{
		if (current->prev && current->prev->input
			&& ft_strcmp(current->prev->input, "<<") == 0)
		{
			current = current->next;
			continue ;
		}
		if (ft_variable_expansion(current, e) == 1)
			return (1);
		current = current->next;
	}
	ft_assign_types(*token);
	return (0);
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
		{
		}
		else if (assign_redirection(current, &is_redirection))
		{
		}
		else if (assign_file(current, &is_redirection))
		{
		}
		else if (assign_cmd_or_arg(current, &is_cmd_context, &is_redirection))
		{
		}
		current = current->next;
	}
}

int	ft_pipe_check(t_token **token)
{
	int		pipes;
	int		cmds;
	t_token	*current;

	pipes = 0;
	cmds = 0;
	current = *token;
	while (current)
	{
		if (current->type == PIPE)
			pipes++;
		else if (current->type == CMD)
			cmds++;
		current = current->next;
	}
	if (cmds - pipes == 0)
		return (1);
	return (0);
}

int	ft_check_tokens(t_token **token, t_expansion *e)
{
	t_token	*node;

	node = *token;
	if (node == NULL)
		return (e->exit_stat = 127, 1);
	if (ft_pipe_check(token) == 1)
		return (e->exit_stat = 127, 1);
	while (node && node->next)
	{
		if (node->type == FORBIDDEN)
			return (e->exit_stat = 127, 1);
		if (((node->type >= 1 && node->type <= 5)
				&& (node->next->type >= 1 && node->next->type <= 5))
			|| (node->type == 1 && node->next->type == 1))
			return (1);
		node = node->next;
	}
	if (node->next == NULL && (node->type >= 1 && node->type <= 5))
		return (e->exit_stat = 127, 1);
	return (0);
}
