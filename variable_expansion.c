#include "parsing.h"

char	*extract_name(char *input, int *i)
{
	int		start;
	char	*name;
	int		len;

	start = *i;
	len = 0;
	while (input[start + len] && (ft_isalnum(input[start + len]) || input[start + len] == '_'))
		len++;
	*i = start + len;
	name = malloc(sizeof(char) * (len + 1));
	if (name == NULL)
		return (error(3, NULL), NULL);
	ft_memcpy(name, input + start, len);
	name[len] = '\0';
	return (name);
}

char	*get_env_value(t_envp **env, char *var_name)
{
	t_envp	*current;

	current = *env;
	while (current)
	{
		if (ft_strcmp(var_name, current->name) == 0)
			return (current->value);
		current = current->next;
	}
	return (NULL);
}

// state values : 0 unquotes, 1 single quotes, 2 double quotes
int	ft_variable_expansion(t_token *token, t_envp **env, int *exit_stat)
{
	char	*res;
	int		i;
	int		state;
	char	*var_value;
	char	*var_name;
	char	*exit_status;

	state = 0;
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
				i++;
				if (token->input[i] == '\0')
				{
					res = ft_strjoin_free(res, "$");
					if (res == NULL)
						return (1);
					i++;
				}
				else if (token->input[i + 1] == '?')
				{
					exit_status = ft_itoa(*exit_stat);
					res = ft_strjoin_free(res, exit_status);
					if (res == NULL)
						return (1);
					i++;
				}
				else
				{
					var_name = extract_name(token->input, &i);
					if (var_name == NULL)
						return (1);
					var_value = get_env_value(env, var_name);
					if (var_value == NULL)
						res = ft_strjoin_free(res, "");
					else
					{
						res = ft_strjoin_free(res, var_value);
						if (res == NULL)
							return (free(var_name), 1);
						i += ft_strlen(var_value);
					}
					// printf("var_value: %s, res: %s, var_name: %s\n", var_value, res, var_name);
					free(var_name);
				}
			}
		}
	}
	free(token->input);
	token->input = malloc(sizeof(char) * (i + 1));
	ft_memcpy(token->input, res, i);
	return (0);
}



















// /* ================================================================== */
// // printf("token = %s\n", current->input);
// // 	WORKS $VAR  prints value for VAR
// 		if (ft_strncmp(token->input, "$", 1) == 0)
// 		{
// 			if (ft_dollar_sign(token, env, exit_stat) != 0)
// 				return (1);
// 		}
// // // "$VAR" prints value for VAR
// // 		if (ft_strncmp(token->input, "\"", 1) == 0)
// // 		{
// // 			if (ft_double_quote_expand(token, env) != 0)
// // 				return (1);
// // 		}
// // // '$VAR' prints $VAR
// // // '"$VAR"' prints "$VAR"
// // 		if (ft_strncmp(token->input, "\'", 1) == 0)
// // 		{
// // 			if (ft_single_quote_expand(token, env) != 0)
// // 				return (1);
// // 		}

// 	return (0);
// }

// int	ft_dollar_sign(t_token *to, t_envp **env, int *exit_stat)
// {
// 	int		i;
// 	t_envp	*e;

// 	e = *env;
// 	if (to->input[1] == '?')
// 		printf("%d\n", *exit_stat);
// 	while (e)
// 	{
// 		if (ft_strncmp(to->input + 1, e->name, ft_strlen(to->input)) == 0)
// 		{
// 			free(to->input);
// 			to->input = malloc(sizeof(char) * ft_strlen(e->value) + 1);
// 			if (to->input == NULL)
// 				return (error(3, NULL), 1);
// 			i = 0;
// 			while (e->value[i])
// 			{
// 				to->input[i] = e->value[i];
// 				i++;
// 			}
// 			to->input[i] = '\0';
// 		}
// 		e = e->next;
// 	}
// 	return (0);
// }

// int	ft_double_quote_expand(t_token *to, t_envp **env)
// {
// 	int		i;
// 	int		j;
// 	t_envp	*e;

// 	e = *env;
// 	while (e)
// 	{
// 		if (ft_strncmp(to->input + 2, e->name, ft_strlen(to->input) - 2) == 0)
// 		{
// 			free(to->input);
// 			to->input = malloc(sizeof(char) * ft_strlen(e->value) + 1);
// 			if (to->input == NULL)
// 				return (error(3, NULL), 1);
// 			i = 0;
// 			j = 1;
// 			while (e->value[i])
// 			{
// 				to->input[i] = e->value[j];
// 				i++;
// 				j++;
// 			}
// 			to->input[i] = '\0';
// 		}
// 		e = e->next;
// 	}
// 	return (0);
// }

// int	ft_single_quote_expand(t_token *to, t_envp **env)
// {
// 	int		i;
// 	char	*temp;
// 	t_envp	*e;

// 	e = *env;
// 	while (e)
// 	{
// 		if (ft_strncmp(to->input + 2, e->name, ft_strlen(to->input) - 2) == 0)
// 		{
// 			temp = malloc(sizeof(char) * ft_strlen(to->input) - 1);
// 			if (to->input == NULL)
// 				return (error(3, NULL), 1);
// 			i = 0;
// 			while (to->input[i + 1])
// 			{
// 				temp[i] = to->input[i + 2];
// 				i++;
// 			}
// 			free(to->input);
// 			temp[i] = '\0';
// 			to->input = temp;
// 		}
// 		e = e->next;
// 	}
// 	return (0);
// }
