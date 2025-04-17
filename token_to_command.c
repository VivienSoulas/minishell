#include "parsing.h"

int	count_commands(t_token **tokens)
{
	int		n;
	t_token	*current;

	n = 0;
	current = *tokens;
	while (current != NULL)
	{
		if (current->type == 0)
			n++;
		current = current->next;
	}
	return (n);
}

int	count_args(t_token *token)
{
	int		n;

	n = 0;
	while (token && token->type != PIPE)
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
	while (*token && (*token)->type == CMD)
	{
		command->args[i] = ft_strdup((*token)->input);
		if (command->args[i] == NULL)
		{
			free(command->executable_path);
			while (i)
				free(command->args[--i]);
			return (error(3, NULL), -1);
		}
		i++;
		*token = (*token)->next;
	}
	command->args[i] = NULL;
	return (0);
}

int	init_redirection(t_token **token, t_command *command)
{
	if (*token != NULL && (*token)->type < 6 && (*token)->type > 0)
	{
		if ((*token)->type == PIPE)
			command->is_pipe = 1;
		else if ((*token)->type == IN)
		{
			*token = (*token)->next;
			command->input_file = ft_strdup((*token)->input);
			if (command->input_file == NULL)
				return (error(3, NULL), -1);
		}
		else if ((*token)->type == HEREDOC)
		{
			command->is_heredoc = 1;
			*token = (*token)->next;
			command->heredoc_delimiter = ft_strdup((*token)->input);
			if (command->heredoc_delimiter == NULL)
				return (error(3, NULL), -1);
		}
		else if ((*token)->type == OUT || (*token)->type == APPEND)
		{
			if ((*token)->type == APPEND)
				command->is_append = 1;
			*token = (*token)->next;
			command->output_file = ft_strdup((*token)->input);
			if (command->output_file == NULL)
				return (error(3, NULL), -1);
		}
		*token = (*token)->next;
	}
	return (0);
}

int	init_command(t_token **token, t_command *cmd, t_envp **envp_list)
{
	int	n_args;

	ft_memset(cmd, 0, sizeof(t_command));
	if (init_redirection(token, cmd) != 0)
		return (-1);
	if (*token != NULL && (*token)->type == 6)
	{
		n_args = count_args(*token);
		cmd->args = ft_calloc(n_args + 1, sizeof(char *));
		if (cmd->args == NULL)
			return (error(3, NULL), -1);
		if (init_args(cmd, token, envp_list) == -1)
			return (-1);
	}
	if (init_redirection(token, cmd) != 0)
		return (-1);
	return (0);
}

void	ft_free_command(t_command **cmd, int n)
{
	int			i;
	int			j;

	if (cmd == NULL || *cmd == NULL)
		return ;
	while (j < n)
	{
		free(cmd[j]->cmd);
		if (cmd[j]->args != NULL)
		{
			while (cmd[j]->args[i])
			{
				i = 0;
				free(cmd[j]->args[i]->input);
				free(cmd[j]->args[i]);
				i++;
			}
			free(cmd[j]->args);
		}
		n++;
		free(cmd[j]);
	}
	free(*cmd);
	*cmd = NULL;
}

t_command	**token_to_cmd(t_token **tokens)
{
	int			cmds;
	int			args;
	t_command	**cmd;
	int			i;
	int			j;

	i = 0;
	cmds = count_commands(tokens);
	if (cmds == 0)
		return (NULL);
	cmd = malloc(sizeof(t_command *) * (cmds + 1));
	if (cmd == NULL)
		return (error(3, NULL), NULL);

	while (i < cmds)
	{
		cmd[i] = malloc(sizeof(t_command));
		if (cmd[i] == NULL)
			return (ft_free_command(cmd, i + 1), error(3, NULL), 1);
		j = 0;
		args = ft_count_args(*tokens) - 1; // removes the cmd token;
		cmd[i]->args = malloc(sizeof(t_token *) * (args + 1));
		if (cmd[i]->args == NULL)
			return (ft_free_command(cmd, i + 1), error(3, NULL), 1);
		while ((*tokens) && (*tokens)->type != PIPE)
		{
			cmd[i]->args[j] = malloc(sizeof(t_token));
			if (cmd[i]->args[j] == NULL)
				return (ft_free_command(cmd, i + 1), error(3, NULL), NULL);
			cmd[i]->args[j]->input = ft_strdup((*tokens)->input);
			if (cmd[i]->args[j]->input == NULL)
				return (ft_free_command(cmd, i + 1), error(3, NULL), NULL);
			cmd[i]->args[j]->type = (*tokens)->type;
			cmd[i]->args[j]->next = (*tokens)->next;
			cmd[i]->args[j]->prev = (*tokens)->prev;
			j++;
			(*tokens) = (*tokens)->next;
		}
		cmd[i]->args[j] = NULL;
		if (*tokens && (*tokens)->type == PIPE)
			i++;
	}
	cmd[i] = NULL;
	return (cmd);
}

// t_command	**token_to_cmd(t_token **tokens, t_envp **envp_list)
// {
// 	t_command	**commands;
// 	int			n_cmd;
// 	int			i;
// 	int			j;
// 	int			n_args = 0;

// 	n_cmd = count_commands(tokens);
// 	commands = ft_calloc(n_cmd + 1, sizeof(t_command *));
// 	if (commands == NULL)
// 		return (error(3, NULL), NULL);
// 	j = 0;
// 	while ((*tokens) && j < n_cmd && (*tokens)->next)
// 	{
// 		i = 0;
// 		if ((*tokens)->type == 0)
// 		{
// 			commands[j] = malloc(sizeof(t_command));
// 			if (commands[j] == NULL)
// 				return (command_cleanup(commands), NULL);
// 			(*commands[j]).cmd = ft_strdup((*tokens)->input);
// 			(*tokens) = (*tokens)->next;
// 			n_args = count_args(*tokens);
// 			printf("n_args:%d\n", n_args);
// 			(*commands[j]).args = malloc(sizeof(char *) * (n_args + 1));
// 			while (i < n_args)
// 			{
// 				(*commands[j]).args[i] = ft_strdup((*tokens)->input);
// 				printf("arg:%s\n", (*commands[j]).args[i]);
// 				i++;
// 				(*tokens) = (*tokens)->next;
// 			}
// 			if ((*commands[j]).args)
// 				(*commands[j]).args[i] = NULL;
// 			j++;
// 		}
// printf("cmd:%s\n", commands[i]->cmd);
// 	(*tokens) = (*tokens)->next;
// 	}
// 	commands[i] = NULL;
// 	return (commands);
// }
