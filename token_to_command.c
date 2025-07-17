/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_to_command.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdavtian <jdavtian@student.codam.nl>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/18 14:56:14 by jdavtian          #+#    #+#             */
/*   Updated: 2025/07/17 12:05:11 by jdavtian         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

int	count_commands(t_token **tokens)
{
	int		n;
	t_token	*current;

	n = 0;
	current = *tokens;
	while (current != NULL)
	{
		if (current->type == CMD && ft_strlen(current->input) != 0)
			n++;
		current = current->next;
	}
	return (n);
}

int	count_args(t_token *token)
{
	int	n;

	n = 0;
	if (token && token->type == CMD)
	{
		n++;
		token = token->next;
	}
	while (token && token->type == ARG)
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
	}
	command->args[i++] = ft_strdup((*token)->input);
	if (command->args[i - 1] == NULL)
		return (error(3, NULL), -1);
	*token = (*token)->next;
	while (*token && (*token)->type == ARG)
	{
		command->args[i] = ft_strdup((*token)->input);
		if (command->args[i] == NULL)
			return (error(3, NULL), -1);
		i++;
		*token = (*token)->next;
	}
	command->args[i] = NULL;
	return (0);
}

int	init_command(t_token **token, t_command *cmd,
	t_envp **envp_list, t_expansion *e)
{
	int	n_args;

	ft_memset(cmd, 0, sizeof(t_command));
	if (init_redirection(token, cmd, e) == -1)
		return (-1);
	n_args = count_args(*token);
	cmd->args = ft_calloc(n_args + 1, sizeof(char *));
	if (cmd->args == NULL)
		return (error(3, NULL), -1);
	if (init_args(cmd, token, envp_list) == -1)
		return (-1);
	if (init_redirection(token, cmd, e) == -1)
		return (-1);
	return (0);
}

t_command	**token_to_cmd(t_token **tokens, t_expansion *e)
{
	t_command	**commands;
	t_token		*current;
	int			n_cmd;
	int			i;

	n_cmd = count_commands(tokens);
	if (n_cmd == 0)
		return (ft_free_list(tokens), NULL);
	commands = ft_calloc(n_cmd + 1, sizeof(t_command *));
	if (commands == NULL)
		return (ft_free_list(tokens), error(3, NULL), NULL);
	e->cmd = commands;
	current = *tokens;
	i = -1;
	while (++i < n_cmd)
	{
		commands[i] = malloc(sizeof(t_command));
		if (commands[i] == NULL
			|| init_command(&current, commands[i], &e->env, e) == -1)
			return (ft_free_list(tokens), NULL);
	}
	commands[i] = NULL;
	return (e->token = tokens, commands);
}
