#include "parsing.h"

int	ft_count_args(char **tokens)
{
	int	i;

	i = 0;
	while (tokens[i])
		i++;
	return (i);
}

void	handler(int sig)
{
	(void)sig;
	printf("\n");
	g_signal_caught = 1;
	rl_on_new_line();
	rl_replace_line("", 0);
	rl_redisplay();
}

void	signals_handling(void)
{
	signal(SIGQUIT, SIG_IGN);
	signal(SIGINT, &handler);
}

void	ft_mem_error(void)
{
	printf("Malloc fail, Exiting Minishell");
}

void	ft_print_exit_status(int *exit)
{
	printf("%d\n", *exit);
}
