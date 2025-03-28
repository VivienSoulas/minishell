#include "parsing.h"

int	count_commands(t_token **tokens)
{
	int		n;
	t_token	*current;

	n = 0;
	current = *tokens;
	while (current != NULL)
	{
		while (current != NULL && current->type < 6)
			current = current->next;
		if (current != NULL)
			n++;
		while (current != NULL && current->type > 5)
			current = current->next;
	}
	return (n);
}

int	count_args(t_token *token)
{
	int	n;

	n = 0;
	while (token && token->type == STRING)
	{
		n++;
		token = token->next;
	}
	return (n);
}

int	init_args(t_command *command, t_token **token, t_envp **envp_list)
{
	int	i;

	i = 0;
	if (is_buildin((*token)->input))
		command->is_buildin = 1;
	else
	{
		command->executable_path = find_executable((*token)->input, envp_list);
		if (command->executable_path == NULL)
			return (-1);
	}
	while (*token && (*token)->type == STRING)
	{
		command->args[i] = ft_strdup((*token)->input);
		if (command->args[i] == NULL)
		{
			free(command->executable_path);
			while (i)
				free(command->args[--i]);
			return (-1);
		}
		i++;
		*token = (*token)->next;
	}
	command->args[i] = NULL;
	return (0);
}

int	init_redirection(t_token **token, t_command *command)
{
	if (*token != NULL && (*token)->type < 6)
	{
		if ((*token)->type == PIPE)
			command->is_pipe = 1;
		else if ((*token)->type == IN)
		{
			*token = (*token)->next;
			command->input_file = ft_strdup((*token)->input);
			if (command->input_file == NULL)
				return (-1);
		}
		else if ((*token)->type == HEREDOC)
		{
			command->is_heredoc = 1;
			*token = (*token)->next;
			command->heredoc_delimiter = ft_strdup((*token)->input);
			if (command->heredoc_delimiter == NULL)
				return (-1);
		}
		else if ((*token)->type == OUT || (*token)->type == OUTP)
		{
			if ((*token)->type == OUTP)
				command->is_append = 1;
			*token = (*token)->next;
			command->output_file = ft_strdup((*token)->input);
			if (command->output_file == NULL)
				return (-1);
		}
		*token = (*token)->next;
	}
	return (0);
}

int	init_command(t_token **token, t_command *command, t_envp **envp_list)
{
	int	n_args;

	ft_memset(command, 0, sizeof(t_command));
	if (init_redirection(token, command) != 0)
		return (-1);
	if (*token != NULL && (*token)->type == 6)
	{
		n_args = count_args(*token);
		command->args = ft_calloc(n_args + 1, sizeof(char *));
		if (command->args == NULL)
			return (-1);
		if (init_args(command, token, envp_list) == -1)
			return (-1);
	}
	if (init_redirection(token, command) != 0)
		return (-1);
	return (0);
}

t_command	**token_to_cmd(t_token **tokens, t_envp **envp_list)
{
	t_command	**commands;
	t_token		*current;
	int			n_cmd;
	int			i;

	n_cmd = count_commands(tokens);
	commands = ft_calloc(n_cmd + 1, sizeof(t_command *));
	if (commands == NULL)
		return (NULL);
	i = 0;
	current = *tokens;
	while (current != NULL)
	{
		commands[i] = malloc(sizeof(t_command));
		if (commands[i] == NULL || init_command(&current, commands[i], envp_list) == -1)
		{
			command_cleanup(commands);
			return (NULL);
		}
		i++;
	}
	commands[i] = NULL;
	return (commands);
}
