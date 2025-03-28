/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vsoulas <vsoulas@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/27 11:04:58 by vsoulas           #+#    #+#             */
/*   Updated: 2025/03/28 18:16:57 by vsoulas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSING_H
# define PARSING_H

# include "libft/libft.h"
# include <stdio.h>
# include <stdlib.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <signal.h>
# include <errno.h>
# include <sys/wait.h>

extern volatile sig_atomic_t	g_signal_caught;

// PIPE (1): pipe symbol ('|') indicating a command pipeline.
// IN (2): input redirection ('<') indicating input redirection from a file.
// OUT (3): redirection ('>') output redirection to a file (overwrite mode).
// HERDOC (4): heredoc ('<<') indicating input redirection from a here-document.
// OUTP (5): output redirection ('>>') output redirection to a file append mode
// STRING (6): regular string token.
// FORBIDDEN (7): forbidden operators.
# define PIPE 1
# define IN 2
# define OUT 3
# define HEREDOC 4
# define OUTP 5
# define STRING 6
# define FORBIDDEN 7

typedef struct s_envp
{
	char			*name;
	char			*value;
	struct s_envp	*next;
	struct s_envp	*prev;
}	t_envp;

typedef struct s_command
{
	char	*executable_path;
	char	**args;
	char	*heredoc_delimiter;
	char	*input_file;
	char	*output_file;
	int		output_fd;
	int		input_fd;
	int		is_append;
	int		is_heredoc;
	int		is_pipe;
	int		is_buildin;
}	t_command;

typedef struct s_split
{
	int		i;
	int		j;
	int		k;
	int		len;
	char	**tokens;
	char	current_token[256];
	char	quote_type;
	int		error;
}	t_split;

// get input and asign it a type from the defines
typedef struct s_token
{
	char			*input;
	int				type;
	struct s_token	*next;
	struct s_token	*prev;
}	t_token;

int			ft_parse_input(char *in, t_envp **env, int *exit, t_token **token);
void		ft_assign_types(t_token *token);
int			ft_variable_expansion(t_token **token, t_envp **env);
int			ft_check_tokens(t_token **token);

t_envp		*copy_envp(char **envp);

// variable expansion
int			ft_dollar_sign(t_token *to, t_envp **env);
int			ft_double_quote_expand(t_token *to, t_envp **env);
int			ft_single_quote_expand(t_token *to, t_envp **env);

// utils
int			ft_count_args(char **tokens);
void		handler(int sig);
void		signals_handling(void);
void		ft_mem_error(void);

// utils list
int			ft_list_tokens(char **tokens, t_token **token);
t_token		*ft_new_node(char *content);
void		ft_add_last(t_token **token, t_token *node);
t_token		*ft_last(t_token **token);

// split
char		**ft_split_input(char *input, t_split *split);
void		ft_handles_double(t_split *split, char *input);
void		ft_handles_operator(t_split *split, char *input);
void		ft_handles_quotes(char *input, t_split *split);
void		ft_handles_string(char *input, t_split *split);

// utils split
int			ft_initialise_split(t_split *split, char *input);
int			ft_check_quotes(char *input);
int			ft_is_operator(char c);
int			ft_double_operator(char *input, int i);

// free
void		ft_free_split(char **split);
void		ft_free_list(t_token **token);
void		ft_free_envp_list(t_envp **envp);

// export
int			ft_export_check(t_envp **env, t_token **token);

/*======================================================================*/
// temp
void		print_token_list(t_token **token);
void		print_double_array(char **array);
int			ft_handle_var(char *input, t_envp **env);
int			ft_temp_exec(t_token **token, t_envp **env);
/*======================================================================*/

// command
t_command	**token_to_cmd(t_token **tokens, t_envp **envp_list);
int			exe_cmds(t_command **commands, t_envp **list);
void		command_cleanup(t_command **commands);
char		*find_executable(char *command, t_envp **envp_list);
int			input_fd(t_command *command, int i, int last_pipe_read);
int			output_fd(t_command *command, int *fd, int is_not_last);
int			exe_command(t_command *command, t_envp **list);
int			init_pipe(int *fd, int last_pipe_read);

// envp
int			add_to_envp(t_envp **envp_list, char *envp);
t_envp		*new_envp(char *envp);
char		*copy_str_delimiter(char *str, int check);
int			add_export_to_envp(t_envp **env, char *export);
char		*env_get_value(t_envp **list, char *name);

int	ft_strcmp(const char *s1, const char *s2);
int	is_buildin(char *command);
int	exec_buildin(t_command *cmd, t_envp **env);
char	**list_to_array(t_envp **list);
void	free_array(char **array);
void	env(t_envp **env);
void	pwd(t_envp **env);
int	ft_replace_value(char *export, t_envp *current);
void	unset(t_command *command, t_envp **list);

#endif
