#include "parsing.h"

// state values : 0 unquotes, 1 single quotes, 2 double quotes
int	ft_variable_expansion(t_token *token, t_envp **env, int *exit)
{
	char	*res;
	int		i;
	int		state;
	int		len;
	char	*result;

	state = 0;
	len = 0;
	res = strdup("");
	if (res == NULL)
		return (error(3, NULL), 1);
	i = 0;
	while (i < (int)ft_strlen(token->input))
	{
		if (state == 0)
		{
			if (token->input[i] == '\'')
			{
				state = 1;
				i++;
			}
			else if (token->input[i] == '\"')
			{
				state = 2;
				i++;
			}
			else if (token->input[i] == '$')
			{
				result = ft_dollar_exp(token, exit, env, &i);
				if (result == NULL)
					return (free(res), 1);
				res = ft_strjoin_free(res, result);
				free(result);
				if (res == NULL)
					return (1);
			}
			else
			{
				result = ft_copy_literal(token, &i);
				if (result == NULL)
					return (1);
				res = ft_strjoin_free(res, result);
				free(result);
				if (res == NULL)
					return (1);
			}
		}
		else if (state == 1)
		{
			result = ft_copy_literal(token, &i);
			if (result == NULL)
				return (1);
			res = ft_strjoin_free(res, result);
			free(result);
			if (res == NULL)
				return (1);
			state = 0;
			i++;
		}
		else if (state == 2)
		{
			result = ft_copy_literal_double(token, &i, env, exit);
			if (result == NULL)
				return (1);
			res = ft_strjoin_free(res, result);
			free(result);
			if (res == NULL)
				return (1);
			state = 0;
			i++;
		}
	}
	free(token->input);
	len = ft_strlen(res);
	token->input = malloc(sizeof(char) * (len + 1));
	if (token->input == NULL)
		return (free(res), error(3, NULL), 1);
	ft_memcpy(token->input, res, len);
	token->input[len] = '\0';
	return (free(res), 0);
}

char	*ft_dollar_exp(t_token *token, int *exit, t_envp **env, int *i)
{
	char	*res;

	res = strdup("");
	if (res == NULL)
		return (error(3, NULL), NULL);
	(*i)++;
	if (token->input[*i] == '\0')
		return ((*i)++, ft_strjoin_free(res, "$"));
	else if (token->input[*i] == '$')
	{
		while (token->input[*i] == '$')
		{
			res = ft_strjoin_free(res, "$");
			(*i)++;
		}
		return ((*i)--, res);
	}
	else if (token->input[*i] == '?')
		return (ft_exit_status(exit, res, i));
	else
		res = ft_no_expansion(token->input, i, env, res);
	return (res);
}

char	*ft_no_expansion(char *input, int *i, t_envp **env, char *res)
{
	char	*var_value;
	char	*var_name;
	char	*result;

	free(res);
	result = strdup("");
	var_name = extract_name(input, i);
	if (result == NULL || var_name == NULL)
		return (free(result), error(3, NULL), NULL);
	var_value = get_env_value(env, var_name);
	if (var_value == NULL)
	result = ft_strjoin_free(result, "");
	else
	result = ft_strjoin_free(result, var_value);
	return (free(var_name), result);
}
