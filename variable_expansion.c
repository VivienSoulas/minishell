#include "parsing.h"

int	ft_dollar_sign(t_token *to, t_envp **env)
{
	int		i;
	t_envp	*e;

	e = *env;
	while (e)
	{
		if (ft_strncmp(to->input + 1, e->name, ft_strlen(to->input) - 1) == 0)
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
