#include "parsing.h"

void	parent(int sig)
{
	if (sig == SIGINT)
	{
		rl_replace_line("", 0);
		rl_on_new_line();
		printf("\n");
		rl_redisplay();
	}
}

void	child(int sig)
{
	if (sig == SIGINT)
	{
		rl_replace_line("", 0);
		rl_on_new_line();
	}
}

void	heredoc(int sig)
{
	if (sig == SIGINT)
	{
		g_heredoc_sigint = 1;
		rl_replace_line("", 0);
		rl_on_new_line();
	}
}

void	sig_hand(int sig)
{
	if (sig == MAIN)
	{
		signal(SIGINT, &parent);
		signal(SIGQUIT, SIG_IGN);
	}
	if (sig == CHILD)
	{
		signal(SIGINT, &child);
		signal(SIGQUIT, &child);
	}
	if (sig == HEREDOC)
	{
		signal(SIGINT, SIG_DFL);
		signal(SIGQUIT, SIG_IGN);
	}
}
