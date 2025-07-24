/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vsoulas <vsoulas@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/10 12:01:17 by vsoulas           #+#    #+#             */
/*   Updated: 2025/04/10 12:01:18 by vsoulas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

char	**ft_split_input(char *input, t_split *s, int exit)
{
	while (s->i < s->len && s->error == 0)
	{
		if (ft_double_operator(input, s->i) == 1)
			ft_handles_double(s, input);
		else if (ft_is_operator(input[s->i]) == 1)
			ft_handles_operator(s, input);
		else if (input[s->i] == '\'' || input[s->i] == '\"')
			ft_handles_quotes(input, s);
		else
			s->current_token[s->k++] = input[s->i++];
		if (s->k != 0 && (ft_is_operator(input[s->i])
				|| input[s->i] == '\0'))
			ft_handles_string(input, s);
	}
	if (s->error != 0)
		return (ft_free_split(s->tokens), s->tokens = NULL, exit = 1, NULL);
	s->tokens[s->j] = NULL;
	return (s->tokens);
}

// handles double operators like << or >>
void	ft_handles_double(t_split *split, char *input)
{
	if (split->k != 0)
	{
		split->current_token[split->k] = '\0';
		split->tokens[split->j] = ft_strdup(split->current_token);
		if (split->tokens[split->j] == NULL)
		{
			split->error = 1;
			return ;
		}
		split->k = 0;
		split->j++;
	}
	split->current_token[0] = input[split->i];
	split->current_token[1] = input[split->i + 1];
	split->current_token[2] = '\0';
	split->tokens[split->j] = ft_strdup(split->current_token);
	if (split->tokens[split->j] == NULL)
	{
		split->error = 1;
		return ;
	}
	split->j++;
	split->i += 2;
}

// handle single operators
void	ft_handles_operator(t_split *split, char *input)
{
	if (split->k != 0)
	{
		split->current_token[split->k] = '\0';
		split->tokens[split->j] = ft_strdup(split->current_token);
		if (split->tokens[split->j] == NULL)
		{
			split->error = 1;
			return ;
		}
		split->k = 0;
		split->j++;
	}
	if (input[split->i] != ' ' && input[split->i] != '\t')
	{
		split->current_token[0] = input[split->i];
		split->current_token[1] = '\0';
		split->tokens[split->j] = ft_strdup(split->current_token);
		if (split->tokens[split->j] == NULL)
		{
			split->error = 1;
			return ;
		}
		split->j++;
	}
	split->i++;
}

// handles quotes
// do not remove quotes
void	ft_handles_quotes(char *input, t_split *split)
{
	split->quote_type = input[split->i];
	split->current_token[split->k++] = input[split->i++];
	while (split->i < split->len && input[split->i] != split->quote_type)
		split->current_token[split->k++] = input[split->i++];
	if (split->i < split->len)
		split->current_token[split->k++] = input[split->i++];
}

// handles strings
void	ft_handles_string(char *input, t_split *split)
{
	(void)input;
	split->current_token[split->k] = '\0';
	split->tokens[split->j++] = ft_strdup(split->current_token);
	if (split->tokens[split->j - 1] == NULL)
	{
		split->error = 1;
		return ;
	}
	split->k = 0;
}
