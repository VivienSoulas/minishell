#include "parsing.h"

void	ft_initialise_expansion(t_expansion *exp, t_envp **env, int *exit)
{
	exp->state = 0;
	exp->i = 0;
	exp->exit = exit;
	exp->env = env;
}

char	*ft_state_0(t_expansion *exp, t_token *token)
{
	char	*result;

	if (token->input[exp->i] == '\'')
	{
		printf("going to state 1\n");
		exp->state = 1;
		exp->i++;
	}
	else if (token->input[exp->i] == '\"')
	{
		printf("going to state 2\n");
		exp->state = 2;
		exp->i++;
	}
	else if (token->input[exp->i] == '$')
		result = ft_dollar_exp(token, exp);
	else
		result = ft_copy_literal(token, exp);
	printf("no state\n");
	printf("result:%s\n", result);
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

	result = ft_copy_literal_double(token, exp);
	exp->state = 0;
	exp->i++;
	return (result);
}

char	*ft_while_loop(t_expansion *exp, t_token *token)
{
	char	*res;
	char	*temp;

	res = ft_strdup("");
	if (res == NULL)
		return (error(3, NULL), NULL);
	while (exp->i < (int)ft_strlen(token->input))
	{
		if (exp->state == 0)
		{
			temp = ft_state_0(exp, token);
			res = ft_strjoin_free(res, temp);
			free(temp);
		}
		else if (exp->state == 1)
			temp = ft_state_1(exp, token);
		else if (exp->state == 2)
		{
			temp = ft_state_2(exp, token);
			res = ft_strjoin_free(res, temp);
			free(temp);
		}
	}
	return (res);
}

// state values : 0 unquotes, 1 single quotes, 2 double quotes
int	ft_variable_expansion(t_token *token, t_envp **env, int *exit)
{
	char		*res;
	int			len;
	t_expansion	*exp;

	exp = malloc(sizeof(t_expansion));
	if (exp == NULL)
		return (error(3, NULL), 1);
	ft_initialise_expansion(exp, env, exit);
	len = 0;
	res = ft_while_loop(exp, token);
	if (res == NULL)
		return (1);
	free(token->input);
	len = ft_strlen(res);
	token->input = malloc(sizeof(char) * (len + 1));
	if (token->input == NULL)
		return (free(res), error(3, NULL), 1);
	ft_memcpy(token->input, res, len);
	token->input[len] = '\0';
	return (free(res), free(exp), 0);
}

char	*ft_dollar_exp(t_token *token, t_expansion *exp)
{
	char	*res;

	res = strdup("");
	if (res == NULL)
		return (error(3, NULL), NULL);
	exp->i++;
	if (token->input[exp->i] == '\0')
		return (exp->i++, ft_strjoin_free(res, "$"));
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
	result = strdup("");
	var_name = extract_name(input, exp);
	if (result == NULL || var_name == NULL)
		return (free(result), error(3, NULL), NULL);
	var_value = get_env_value(exp->env, var_name);
	if (var_value == NULL)
	result = ft_strjoin_free(result, "");
	else
	result = ft_strjoin_free(result, var_value);
	return (free(var_name), result);
}
