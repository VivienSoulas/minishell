/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vsoulas <vsoulas@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/27 11:04:58 by vsoulas           #+#    #+#             */
/*   Updated: 2025/03/06 15:05:03 by vsoulas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSING_H
# define PARSING_H

# include "libft/libft.h"
# include <stdio.h>
# include <stdlib.h>
# include <readline/readline.h>
# include <readline/history.h>

// PIPE (1): pipe symbol ('|') indicating a command pipeline.
// IN (2): input redirection ('<') indicating input redirection from a file.
// OUT (3): redirection ('>') output redirection to a file (overwrite mode).
// HERDOC (4): heredoc ('<<') indicating input redirection from a here-document.
// OUTP (5): output redirection ('>>') output redirection to a file append mode
// STRING (6): regular string token.
// ECHO (7) take care of echo -n possibility.
# define PIPE 1
# define IN 2
# define OUT 3
# define HEREDOC 4
# define OUTP 5
# define STRING 6
# define ECHO 7

// get input and asign it a type from the defines
typedef struct s_token
{
	char			*input;
	int				type;
	struct s_token	*next;
	struct s_token	*prev;
}	t_token;

typedef struct s_dollar
{
	int		seen;
	char	*value;
}	t_dollar;

int		ft_parse_input(char *in, char **env, int *exit_stat, t_token **token);
int		ft_tokenise(char **tokens, t_token **token);
int		ft_check_token(t_token *token, char **env);
//int		ft_dollar_asign(t_token *token, t_dollar *dollar);
//int		ft_fill_arg(t_token *token, t_dollar *dollar);

// utils
int		ft_count_args(char **tokens);
int		ft_handle_one(char *input, char **env);

// utils list
t_token	*ft_new_node(char *content);
void	ft_add_last(t_token **token, t_token *node);
t_token	*ft_last(t_token **token);

// free
void	ft_free(char **tokens, t_token **token);
void	ft_free_split(char **split);
void	ft_free_list(t_token **token);

/*======================================================================*/
void	print_token_list(t_token **token);
/*======================================================================*/

#endif