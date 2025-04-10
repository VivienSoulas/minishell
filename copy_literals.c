/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   copy_literals.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vsoulas <vsoulas@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/10 12:00:45 by vsoulas           #+#    #+#             */
/*   Updated: 2025/04/10 12:00:46 by vsoulas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

char	*ft_copy_literal(t_token *token, t_expansion *exp)
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

    result = strdup(""); // Initialize result
    if (result == NULL)
        return (error(3, NULL), NULL);

    while (token->input[exp->i] && token->input[exp->i] != '\"')
    {
        if (token->input[exp->i] == '$') // Handle variable expansion
        {
            substring = ft_dollar_exp(token, exp);
            if (substring == NULL)
                return (free(result), NULL);
            result = ft_strjoin_free(result, substring);
            free(substring);
            if (result == NULL)
                return (NULL);
        }
        else if (token->input[exp->i] == '\'') // Handle nested single quotes
        {
            exp->i++; // Skip opening single quote
            start = exp->i;
            while (token->input[exp->i] && token->input[exp->i] != '\'')
				exp->i++;
            if (token->input[exp->i] == '\'') // Closing single quote
            {
                substring = ft_substr(token->input, start, exp->i - start);
                if (substring == NULL)
                    return (free(result), error(3, NULL), NULL);
                result = ft_strjoin_free(result, substring);
                free(substring);
                if (result == NULL)
                    return (NULL);
				exp->i++; // Skip closing single quote
            }
		}
        else // Handle literal characters
        {
            start = exp->i;
            while (token->input[exp->i] && token->input[exp->i] != '\"' &&
                   token->input[exp->i] != '$' && token->input[exp->i] != '\'')
				exp->i++;
            substring = ft_substr(token->input, start, exp->i - start);
            if (substring == NULL)
                return (free(result), error(3, NULL), NULL);
            result = ft_strjoin_free(result, substring);
            free(substring);
            if (result == NULL)
                return (NULL);
        }
    }
    return (result);
}
