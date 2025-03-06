#include "parsing.h"

int	ft_count_args(char **tokens)
{
	int	i;

	i = 0;
	while (tokens[i])
		i++;
	return (i);
}

// could handle pwd better by looking for "pwd" in env & return its output
int	ft_handle_one(char *input, char **env)
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
	else if (ft_strncmp(input, "exit", 5) == 0)
		return (1);
	return (0);
}

/*======================================================================*/
void print_token_list(t_token **token)
{
	t_token *trial;

	trial = *token;
    while (trial != NULL)
    {
        printf("Token: %s, Type: %d\n", trial->input, trial->type);
        trial = trial->next;
    }
}
/*======================================================================*/
