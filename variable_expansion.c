/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   variable_expansion.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vsoulas <vsoulas@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/10 12:01:41 by vsoulas           #+#    #+#             */
/*   Updated: 2025/05/29 16:26:48 by vsoulas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

char	*ft_while_loop(t_expansion *exp, t_token *token)
{
	char	*res;
	char	*temp;
	char	*(*state_funcs [3])(t_expansion *, t_token *);

	exp->i = 0;
	state_funcs[0] = ft_state_0;
	state_funcs[1] = ft_state_1;
	state_funcs[2] = ft_state_2;
	res = ft_strdup("");
	if (res == NULL)
		return (error(3, NULL), NULL);
	while (exp->i < (int)ft_strlen(token->input))
	{
		temp = state_funcs[exp->state](exp, token);
		if (temp != NULL)
		{
			res = ft_strjoin_free(res, temp);
			free(temp);
		}
	}
	return (res);
}

// state values : 0 unquotes, 1 single quotes, 2 double quotes
int	ft_variable_expansion(t_token *token, t_expansion *e)
{
	char		*res;
	int			len;

	len = 0;
	res = ft_while_loop(e, token);
	if (res == NULL)
		return (1);
	free(token->input);
	token->input = NULL;
	len = ft_strlen(res);
	token->input = malloc(sizeof(char) * (len + 1));
	if (token->input == NULL)
		return (free(res), error(3, NULL), 1);
	ft_memcpy(token->input, res, len);
	token->input[len] = '\0';
	return (free(res), 0);
}

char	*ft_dollar_exp(t_token *token, t_expansion *exp)
{
	char	*res;

	res = ft_strdup("");
	if (res == NULL)
		return (error(3, NULL), NULL);
	exp->i++;
	if (token->input[exp->i] == '\0')
		return (ft_strjoin_free(res, "$"));
	else if (token->input[exp->i] == '$')
	{
		while (token->input[exp->i] == '$')
		{
			res = ft_strjoin_free(res, "$");
			exp->i++;
		}
		return (exp->i--, res);
	}
	else if (token->input[exp->i] == '?')
		return (ft_exit_status(res, exp));
	else if (!ft_isalnum(token->input[exp->i]) && token->input[exp->i] != '_')
		return (ft_strjoin_free(res, "$"));
	else
		res = ft_no_expansion(token->input, res, exp);
	return (res);
}

char	*ft_no_expansion(char *input, char *res, t_expansion *exp)
{
	char	*var_value;
	char	*var_name;
	char	*result;

	free(res);
	result = ft_strdup("");
	var_name = extract_name(input, exp);
	if (result == NULL || var_name == NULL)
		return (free(result), error(3, NULL), NULL);
	var_value = get_env_value(&exp->env, var_name);
	if (var_value == NULL)
		result = ft_strjoin_free(result, "");
	else
		result = ft_strjoin_free(result, var_value);
	return (free(var_name), result);
}
