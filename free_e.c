#include "parsing.h"

void	ft_free_e(t_expansion **e)
{
	if (!e && !(*e))
		return ;
	if ((*e)->env)
	{
		ft_free_envp_list(&(*e)->env);
		free((*e)->env);
		(*e)->env = NULL;
	}
	if ((*e)->envp)
	{
		free_array((*e)->envp);
		(*e)->envp = NULL;
	}
	ft_free_e_2(e);
	free(*e);
	*e = NULL;
}

void	ft_free_e_2(t_expansion **e)
{
	if ((*e)->cmd)
	{
		command_cleanup((*e)->cmd);
		(*e)->cmd = NULL;
	}
	if ((*e)->token)
	{
		ft_free_list((*e)->token);
		(*e)->token = NULL;
	}
	if ((*e)->pids)
	{
		free((*e)->pids);
		(*e)->pids = NULL;
	}
	if ((*e)->initial_stdin != -1)
		close((*e)->initial_stdin);
	if ((*e)->initial_stdout != -1)
		close((*e)->initial_stdout);
}
