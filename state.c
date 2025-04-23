/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   state.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vsoulas <vsoulas@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/10 12:01:20 by vsoulas           #+#    #+#             */
/*   Updated: 2025/04/18 15:48:20 by vsoulas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

char	*ft_state_0(t_expansion *exp, t_token *token)
{
	char	*result;

	result = NULL;
	if (token->input[exp->i] == '\'')
	{
		exp->state = 1;
		exp->i++;
	}
	else if (token->input[exp->i] == '\"')
	{
		exp->state = 2;
		exp->i++;
	}
	else if (token->input[exp->i] == '$')
		result = ft_dollar_exp(token, exp);
	else
		result = ft_copy_literal(token, exp);
	return (result);
}

char	*ft_state_1(t_expansion *exp, t_token *token)
{
	char	*result;

	result = ft_copy_literal(token, exp);
	exp->state = 0;
	exp->i++;
	return (result);
}

char	*ft_state_2(t_expansion *exp, t_token *token)
{
	char	*result;
	char	*temp;

	result = NULL;
	if (token->input[exp->i + 1] && token->input[exp->i] == '\"'
		&& token->input[exp->i + 1] == '\"')
	{
		temp = ft_strdup("");
		if (temp == NULL)
			return (error(3, NULL), NULL);
		result = ft_strjoin_free(result, temp);
		free(temp);
		ft_state_0(exp, token);
	}
	else
	{
		result = ft_copy_literal_double(token, exp);
		exp->state = 0;
		exp->i++;
	}
	return (result);
}
