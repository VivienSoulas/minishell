/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   copy_literals.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vsoulas <vsoulas@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/10 12:32:02 by vsoulas           #+#    #+#             */
/*   Updated: 2025/04/18 15:59:34 by vsoulas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

char	*ft_copy_literal(t_token *token, t_expansion *exp)
{
	char	*substring;
	int		start;

	start = exp->i;
	while (token->input[exp->i] && token->input[exp->i] != '\'' 
		&& token->input[exp->i] != '\"' && token->input[exp->i] != '$')
		exp->i++;
	substring = ft_substr(token->input, start, exp->i - start);
	if (substring == NULL)
		return (error(3, NULL), NULL);
	return (substring);
}

char	*ft_copy_literal_single(t_token *token, t_expansion *exp)
{
	char	*substring;
	int		start;

	start = exp->i;
	while (token->input[exp->i] && token->input[exp->i] != '\'')
		exp->i++;
	substring = ft_substr(token->input, start, exp->i - start);
	if (substring == NULL)
		return (error(3, NULL), NULL);
	return (substring);
}

char	*ft_copy_literal_double(t_token *token, t_expansion *exp)
{
	char	*substring;
	char	*result;
	int		start;

	result = strdup("");
	if (result == NULL)
		return (error(3, NULL), NULL);
	while (token->input[exp->i] && token->input[exp->i] != '\"')
	{
		if (token->input[exp->i] == '$')
			substring = ft_dollar_exp(token, exp);
		else
		{
			start = exp->i;
			while (token->input[exp->i] && token->input[exp->i] != '$'
				&& token->input[exp->i] != '\"')
				exp->i++;
			substring = ft_substr(token->input, start, exp->i - start);
		}
		if (substring == NULL)
			return (free(result), NULL);
		result = ft_strjoin_free(result, substring);
		free(substring);
	}
	return (result);
}
