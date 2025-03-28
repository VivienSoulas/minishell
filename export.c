#include "parsing.h"

// check if value was already set and if so replace with new input
int	ft_export_check(t_envp **env, t_token **token)
{
	t_token	*current;

	current = *token;
	if (ft_strncmp(current->input, "export", 7) == 0 && current->prev == NULL)
	{
// should print envp sorted by alphabetic order cap first lower last
		if (current->next == NULL)
			return (printf("Invalid input, printing envp\n"), 0);
// if no equal sign value = value
		if (ft_strchr(current->next->input, '=') == 0)
		{
			printf("no equal sign\n");
			return (0);
		}
// WORKING if no arg value = ""
		if (add_export_to_envp(env, current->next->input) == 1)
			return (1);
	}
	return (0);
}

int	add_export_to_envp(t_envp **env, char *export)
{
	t_envp	*current;
	t_envp	*new;
	int		len;

	len = ft_strlen(export);
	current = *env;
	while (current->next)
	{
// check for already existing var name and replace its value
		if (ft_strncmp(current->name, export, len) == 0)
		{
			ft_delete_node(env, export);
			break ;
		}
		current = current->next;
	}
	new = new_envp(export);
	if (new == NULL)
		return (1);
// insert new_node where it needs to be
	new->next = NULL;
	current->next = new;
	return (0);
}

//void	ft_delete_node(t_envp **env, char *export)
//{
//	t_envp	*current;
//	t_envp	*prev;
//	t_envp	*next;
//	int		len;

//	len = ft_strlen(export);
//	current = *env;
//	while (current->next)
//	{
//		prev = current->prev;
//		next = current->next;
//		if (ft_strncmp(current->name, export, len) == 0)
//		{
//			free(current->name);
//			free(current->value);
//			free(current);
//			break ;
//		}
//		current = current->next;
//	}
//	prev->next = next;
//}
