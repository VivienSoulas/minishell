#include "parsing.h"

char	*extract_name(char *input, int *i)
{
	int		start;
	char	*name;
	int		len;

	start = *i;
	len = 0;
	while (input[start + len]
		&& ((ft_isalnum(input[start + len]) || input[start + len] == '_')))
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

char	*ft_copy_literal(t_token *token, int *i)
{
	char	*substring;
	int		start;

	start = *i;
	while (token->input[*i] && token->input[*i] != '\'')
		(*i)++;
	substring = ft_substr(token->input, start, *i - start);
	if (substring == NULL)
		return (error(3, NULL), NULL);
	return (substring);
}

char	*ft_exit_status(int	*exit, char *res, int *i)
{
	char	*exit_status;

	exit_status = ft_itoa(*exit);
	if (exit_status == NULL)
		return (error(3, NULL), NULL);
	res = ft_strjoin_free(res, exit_status);
	if (res == NULL)
		return (free(exit_status), NULL);
	free(exit_status);
	(*i)++;
	return (res);
}

char	*ft_copy_literal_double(t_token *token, int *i, t_envp **env, int *exit)
{
    char	*substring;
    char	*result;
    int		start;

    result = strdup(""); // Initialize result
    if (result == NULL)
        return (error(3, NULL), NULL);

    while (token->input[*i] && token->input[*i] != '\"')
    {
        if (token->input[*i] == '$') // Handle variable expansion
        {
            substring = ft_dollar_exp(token, exit, env, i);
            if (substring == NULL)
                return (free(result), NULL);
            result = ft_strjoin_free(result, substring);
            free(substring);
            if (result == NULL)
                return (NULL);
        }
        else if (token->input[*i] == '\'') // Handle nested single quotes
        {
            (*i)++; // Skip opening single quote
            start = *i;
            while (token->input[*i] && token->input[*i] != '\'')
                (*i)++;
            if (token->input[*i] == '\'') // Closing single quote
            {
                substring = ft_substr(token->input, start, *i - start);
                if (substring == NULL)
                    return (free(result), error(3, NULL), NULL);
                result = ft_strjoin_free(result, substring);
                free(substring);
                if (result == NULL)
                    return (NULL);
                (*i)++; // Skip closing single quote
            }
		}
        else // Handle literal characters
        {
            start = *i;
            while (token->input[*i] && token->input[*i] != '\"' &&
                   token->input[*i] != '$' && token->input[*i] != '\'')
                (*i)++;
            substring = ft_substr(token->input, start, *i - start);
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
