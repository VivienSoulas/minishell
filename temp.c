#include "parsing.h"


/*======================================================================*/
void	print_token_list(t_token **token)
{
	t_token	*trial;
	int		i;

	trial = *token;
	i = 0;
	while (trial != NULL)
	{
		printf("Token[%i]: %s, Type: %d\n", i, trial->input, trial->type);
		trial = trial->next;
		i++;
	}
}
void	print_double_array(char **array)
{
	int	i;

	i = 0;
	while (array[i])
	{
		printf("array[%i] = %s\n", i, array[i]);
		i++;
	}
}

int	ft_temp_exec(t_token **token, char **env)
{

	t_token *current;

	current = *token;
	while (current)
	{
		if (ft_strncmp(current->input, "env", 3) == 0
		|| ft_strncmp(current->input, "pwd", 3) == 0
		|| ft_strncmp(current->input, "exit", 5) == 0
		|| ft_strncmp(current->input, "trial", 6) ==0)
		{
			if (ft_handle_var(current->input, env) == 1)
			return (1);
		}
		current = current->next;
	}
	return (0);
}

int	ft_handle_var(char *input, char **env)
{
	int		i;
	char	*pwd;
	char	*buf;

	buf = NULL;
	if (ft_strncmp(input, "pwd", 3) == 0)
	{
		pwd = getcwd(buf, 1024);
		printf("%s\n", pwd);
		free(pwd);
	}
	else if (ft_strncmp(input, "env", 3) == 0)
	{
		i = 0;
		while (env[i])
		{
			printf("%s\n", env[i]);
			i++;
		}
	}
	else if (ft_strncmp(input, "trial", 6) == 0)
	{
		i = 0;
		while (i >= 0)
		{
			if (g_signal_caught == 1)
			{
				printf("signal caught\n");
				break ;
			}
			printf("%i\n", i);
			i++;
		}
	}
	else if (ft_strncmp(input, "exit", 5) == 0)
		return (1);
	return (0);
}
/*======================================================================*/