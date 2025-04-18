/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   assign_type.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vsoulas <vsoulas@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/11 16:00:36 by vsoulas           #+#    #+#             */
/*   Updated: 2025/04/18 13:22:12 by vsoulas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

int	assign_pipe(t_token *current, int *is_cmd, int *is_red)
{
	if (ft_strncmp(current->input, "|", 1) == 0)
	{
		current->type = PIPE;
		*is_cmd = 1;
		*is_red = 0;
		return (1);
	}
	return (0);
}

int	assign_redirection(t_token *current, int *is_red)
{
	if (ft_strncmp(current->input, "<<", 2) == 0)
	{
		current->type = HEREDOC;
		*is_red = HEREDOC;
	}
	else if (ft_strncmp(current->input, ">>", 2) == 0)
	{
		current->type = APPEND;
		*is_red = OUTFILE;
	}
	else if (ft_strncmp(current->input, "<", 1) == 0)
	{
		current->type = IN;
		*is_red = INFILE;
	}
	else if (ft_strncmp(current->input, ">", 1) == 0)
	{
		current->type = OUT;
		*is_red = OUTFILE;
	}
	if (current->type != -1)
		return (1);
	return (0);
}

int	assign_file(t_token *current, int *is_red)
{
	if (*is_red == INFILE)
	{
		current->type = INFILE;
		*is_red = 0;
	}
	else if (*is_red == OUTFILE)
	{
		current->type = OUTFILE;
		*is_red = 0;
	}
	else if (*is_red == HEREDOC)
	{
		current->type = 10;
		*is_red = 0;
	}
	if (current->type != -1)
		return (1);
	return (0);
}

int	assign_cmd_or_arg(t_token *current, int *is_cmd, int *is_red)
{
	if (*is_cmd == 1)
	{
		current->type = CMD;
		*is_cmd = 0;
		return (1);
	}
	else
	{
		if (current->prev && current->prev->type == CMD)
		{
			while (current && current->type == -1
				&& (assign_pipe(current, is_cmd, is_red) == 0
					&& assign_redirection(current, is_red) == 0
					&& assign_file(current, is_red) == 0))
			{
				current->type = ARG;
				current = current->next;
			}
		}
		else
			current->type = 0;
		return (1);
	}
	return (0);
}
