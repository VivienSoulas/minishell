/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vsoulas <vsoulas@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/27 11:04:58 by vsoulas           #+#    #+#             */
/*   Updated: 2025/05/29 13:57:18 by vsoulas          ###   ########.fr       */
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
# include <stdbool.h>

extern volatile sig_atomic_t	g_signal_caught;

// PIPE (1): pipe symbol ('|') indicating a command pipeline.
// IN (2): input redirection ('<') indicating input redirection from a file.
// OUT (3): redirection ('>') output redirection to a file (overwrite mode).
// HERDOC (4): heredoc ('<<') indicating input redirection from a here-document.
// OUTP (5): output redirection ('>>') output redirection to a file append mode
// STRING (6): regular string token.
// FORBIDDEN (7): forbidden operators.
# define CMD 0
# define PIPE 1
# define IN 2
# define OUT 3
# define HEREDOC 4
# define APPEND 5
# define ARG 6
# define FORBIDDEN 7
# define INFILE 8
# define OUTFILE 9
# define HEREDOC_DELIMITER 10

# define PATH_MAX 4096

// struct to keep variables for export expansion
typedef struct s_variable
{
	char	*name;
	char	*value;
	char	*res;
}	t_variable;

// struct to copy envp and used for export and unset
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

// struct to manage split of tokens
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

// struct to keep expansion variable norminette friendly
typedef struct s_expansion
{
	int		state;
	int		i;
	int		exit;
	int		exit_stat;
	t_envp	*env;
}	t_expansion;

// main
int			ft_loop(t_token **token, t_expansion *e);
int			ft_parse_input(char *in, t_expansion *e, t_token **token);
void		ft_assign_types(t_token *token);
int			ft_check_tokens(t_token **token);

// utils pasing
int			ft_pipe_check(t_token **token);

// assign type
int			assign_pipe(t_token *current, int *is_cmd, int *is_red);
int			assign_redirection(t_token *current, int *is_red);
int			assign_file(t_token *current, int *is_red);
int			assign_cmd_or_arg(t_token *current, int *is_cmd, int *is_red);

// build-in
int			is_buildin(char *command);
int			exec_buildin(t_command *cmd, t_expansion *e, t_token **t);
int			env(t_envp **env, t_token **t, t_expansion *e);
void		pwd(t_envp **env);
int			echo(t_token **token, t_expansion *e, int fd);
int			cd(t_command *cmd, t_expansion *e);

// utils
int			ft_count_args(char **tokens);
void		handler(int sig);
void		signals_handling(void);
char		*ft_strjoin_free(char *s1, char *s2);
int			ft_initialise_expansion(t_expansion *exp, char **env);

// utils list
int			ft_list_tokens(char **tokens, t_token **token);
t_token		*ft_new_node(char *content);
void		ft_add_last(t_token **token, t_token *node);
t_token		*ft_last(t_token **token);

// split
char		**ft_split_input(char *input, t_split *split, int exit);
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
void		free_array(char **array);
void		ft_free_e(t_expansion **e);

// export
int			ft_export_check(t_token **token, t_expansion *e);
int			ft_print_export(t_envp **env);
int			add_export_to_envp(t_envp **env, char *value, char *name);
t_envp		*ft_new_export(char *value, char *name);
int			ft_crop(t_token *token);

// export equal
int			ft_export_equal(t_token *current, t_expansion *e);
int			ft_dollar(t_token *cur, t_variable *vari, t_expansion *e);

// utils export
int			is_valid(char *str);
int			ft_replace_value(char *export, t_envp *current);
void		ft_sort_list(t_envp **array, int total);
int			ft_compare_names(char *name1, char *name2);
void		ft_print(t_envp **list, int total);

// variable expansion
char		*ft_while_loop(t_expansion *exp, t_token *token);
int			ft_variable_expansion(t_token *token, t_expansion *e);
char		*ft_dollar_exp(t_token *token, t_expansion *exp);
char		*ft_no_expansion(char *input, char *res, t_expansion *exp);

// utils variable expansion
char		*extract_name(char *input, t_expansion *exp);
char		*get_env_value(t_envp **env, char *var_name);
char		*ft_exit_status(char *res, t_expansion *exp);
// char		*ft_strip(char *res);

// copy literals
char		*ft_copy_literal(t_token *token, t_expansion *exp);
char		*ft_copy_literal_single(t_token *token, t_expansion *exp);
char		*ft_copy_literal_double(t_token *token, t_expansion *exp);

// state
char		*ft_state_0(t_expansion *exp, t_token *token);
char		*ft_state_1(t_expansion *exp, t_token *token);
char		*ft_state_2(t_expansion *exp, t_token *token);

// error
void		error(int i, char *str);

// exit
int			ft_exit(t_expansion *e, t_command *cmd);
int			ft_atoi_exit(const char *nptr);
int			ft_isnum_exit(char *str);

// commandes free
void		free_strings(t_command *command);
void		command_cleanup(t_command **commands);

// copy envp
char		*copy_str_delimiter(char *str, int check);
t_envp		*new_envp(char *envp);
int			add_to_envp(t_envp **envp_list, char *envp);
t_envp		*copy_envp(char **envp);

// env utils
int			ft_strcmp(const char *s1, const char *s2);
char		*env_get_value(t_envp **list, char *name);
int			init_array(char **res, t_envp **list);
char		**list_to_array(t_envp **list);

// exec
void		pipe_manage(int is_not_last, int *last_pipe_read, int *fd);
int			init_pipe(int *fd, int last_pipe_read);
int			exe_cmds(t_command **c, t_expansion *e, t_token **token);

// find exec
char		*find_executable_in_path(char *command);
char		*find_executable_in_directory(char *command, char *directory);
void		free_directories(char **directories);
char		*find_executable(char *command, t_envp **envp_list);

// in out
int			input_fd(t_command *command, int i, int last_pipe_read);
int			output_fd(t_command *command, int *fd, int is_not_last);

// process
int			line_read(char *delim, int *here_pipe, int expand, t_expansion *e);
void		readline_here(char *delimiter, t_expansion *e);
int			handle_redirection(t_command *command, t_expansion *e);
void		exe_child(t_command *c, char **envp, t_expansion *e);
int			exe_buildin(t_command *c, t_expansion *e, t_token **t);
int			exe_command(t_command *c, t_expansion *e, t_token **t);

// utils process
void		close_fds(t_command *command);
void		reset_fds(int i_stdin, int i_stdout);
int			ft_heredoc_delimiter(int *expand, char **delimiter);
int			ft_fd_0(t_command *command);

// token to command
int			count_commands(t_token **tokens);
int			count_args(t_token *token);
int			init_args(t_command *command, t_token **token, t_envp **envp_list);
int			init_redirection(t_token **token, t_command *command);
int			init_command(t_token **token, t_command *cmd, t_envp **envp_list);
t_command	**token_to_cmd(t_token **tokens, t_envp **envp_list);

// unset
void		unset(t_command *command, t_envp **list);
void		ft_free_env(t_envp *current);

#endif
