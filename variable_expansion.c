#include "parsing.h"

int	ft_variable_expansion(t_token **token, t_envp **env)
{
	t_token	*current;

	current = *token;
	while (current)
	{
		if (ft_strncmp(current->input, "$", 1) == 0)
		{
			//if (ft_strncmp(current->input + 1, "?", 1) == 0)
			//	ft_print_exit_status(exit);
			//else
			if (ft_dollar_sign(current, env) != 0)
				return (1);
		}
// "$VAR" prints value for VAR
// 	$VAR  prints value for VAR

// '$VAR' prints $VAR
// '"$VAR"' prints "$VAR"
		if (ft_strncmp(current->input, "\"", 1) == 0)
		{
			if (ft_double_quote_expand(current, env) != 0)
				return (1);
		}
		if (ft_strncmp(current->input, "\'", 1) == 0)
		{
			if (ft_single_quote_expand(current, env) != 0)
				return (1);
		}
		current = current->next;
	}
	return (0);
}

int	ft_dollar_sign(t_token *to, t_envp **env)
{
	int		i;
	t_envp	*e;

	e = *env;
	while (e)
	{
		if (ft_strncmp(to->input + 1, e->name, ft_strlen(to->input)) == 0)
		{
			free(to->input);
			to->input = malloc(sizeof(char) * ft_strlen(e->value) + 1);
			if (to->input == NULL)
				return (1);
			i = 0;
			while (e->value[i])
			{
				to->input[i] = e->value[i];
				i++;
			}
			to->input[i] = '\0';
		}
		e = e->next;
	}
	return (0);
}

int	ft_double_quote_expand(t_token *to, t_envp **env)
{
	int		i;
	t_envp	*e;

	e = *env;
	while (e)
	{
		if (ft_strncmp(to->input + 2, e->name, ft_strlen(to->input) - 2) == 0)
		{
			free(to->input);
			to->input = malloc(sizeof(char) * ft_strlen(e->value) + 1);
			if (to->input == NULL)
				return (1);
			i = 0;
			while (e->value[i])
			{
				to->input[i] = e->value[i];
				i++;
			}
			to->input[i] = '\0';
		}
		e = e->next;
	}
	return (0);
}

int	ft_single_quote_expand(t_token *to, t_envp **env)
{
	int		i;
	char	*temp;
	t_envp	*e;

	e = *env;
	while (e)
	{
		if (ft_strncmp(to->input + 2, e->name, ft_strlen(to->input) - 2) == 0)
		{
			temp = malloc(sizeof(char) * ft_strlen(to->input) - 1);
			if (to->input == NULL)
				return (1);
			i = 0;
			while (to->input[i + 1])
			{
				temp[i] = to->input[i + 2];
				i++;
			}
			free(to->input);
			temp[i] = '\0';
			to->input = temp;
		}
		e = e->next;
	}
	return (0);
}
