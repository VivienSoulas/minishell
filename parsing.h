/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vsoulas <vsoulas@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/27 11:04:58 by vsoulas           #+#    #+#             */
/*   Updated: 2025/04/10 11:59:23 by vsoulas          ###   ########.fr       */
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

// struct for 
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

typedef struct s_expansion
{
	int		state;
	t_token	*token;
	int		i;
	int		*exit;
	t_envp	**env;
}	t_expansion;

// array of function declaration
typedef char	*(*state_func)(t_expansion *, t_token *);

// main
int			ft_loop(int *exit_stat, t_token **token, t_envp **env, int *exit_c);
int			ft_parse_input(char *in, int *exit, t_token **token);
void		ft_assign_types(t_token *token);
int			ft_check_tokens(t_token **token);

// build-in
int			is_buildin(char *command);
int			exec_buildin(t_command *cmd, t_envp **envp, int *exit);
void		env(t_envp **env);
void		pwd(t_envp **env);
int			echo(t_token **token, t_envp **env, int *exit_stat);

// utils
int			ft_count_args(char **tokens);
void		handler(int sig);
void		signals_handling(void);
char		*ft_strjoin_free(char *s1, char *s2);
void		ft_initialise_expansion(t_expansion *exp, t_envp **env, int *exit);

// utils list
int			ft_list_tokens(char **tokens, t_token **token);
t_token		*ft_new_node(char *content);
void		ft_add_last(t_token **token, t_token *node);
t_token		*ft_last(t_token **token);

// split
char		**ft_split_input(char *input, t_split *split, int *exit);
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
int			ft_crop(t_token *token);
int			ft_export_check(t_envp **env, t_token **token, int *exit_stat);
int			add_export_to_envp(t_envp **env, char *value, char *name);
t_envp		*ft_new_export(char *value, char *name);
int			ft_print_export(t_envp **env);

// utils export
int			ft_replace_value(char *export, t_envp *current);
int			is_valid(char *str);
void		ft_print(t_envp **list, int total);
int			ft_compare_names(char *name1, char *name2);
void		ft_sort_list(t_envp **array, int total);

// export equal
int			ft_export_equal(t_token *current, int *exit_stat, t_envp **env);
int			ft_dollar(t_token *cur, t_variable *vari, t_envp **env, int *exit);

// variable expansion
char		*ft_while_loop(t_expansion *exp, t_token *token);
int			ft_variable_expansion(t_token *token, t_envp **env, int *exit);
char		*ft_dollar_exp(t_token *token, t_expansion *exp);
char		*ft_no_expansion(char *input, char *res, t_expansion *exp);

// utils variable expansion
char		*extract_name(char *input, t_expansion *exp);
char		*get_env_value(t_envp **env, char *var_name);
char		*ft_exit_status(char *res, t_expansion *exp);

// copy literals
char		*ft_copy_literal(t_token *token, t_expansion *exp);
char		*ft_copy_literal_double(t_token *token, t_expansion *exp);

// state
char		*ft_state_0(t_expansion *exp, t_token *token);
char		*ft_state_1(t_expansion *exp, t_token *token);
char		*ft_state_2(t_expansion *exp, t_token *token);

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
// static int	count_list(t_envp **list);
int			init_array(char **res, t_envp **list);
void		free_array(char **array);
char		**list_to_array(t_envp **list);

// exec
void		pipe_manage(int is_not_last, int *last_pipe_read, int *fd);
int			init_pipe(int *fd, int last_pipe_read);
// static int	command_count(t_command **commands);
// static void	cleanup_fd(int *fd, int last_read_pipe);
int			exe_cmds(t_command **commands, t_envp **list, int *exit);

// find exec
char		*find_executable_in_path(char *command);
char		*find_executable_in_directory(char *command, char *directory);
void		free_directories(char **directories);
char		*find_executable(char *command, t_envp **envp_list);

// in out
// static int	open_input_file(t_command *command);
// static int	open_output_file(t_command *command);
int			input_fd(t_command *command, int i, int last_pipe_read);
int			output_fd(t_command *command, int *fd, int is_not_last);

// process
// static void	close_fds(t_command *command);
int			line_read(char *delimiter, int *here_pipe);
void		readline_here(char *delimiter);
// static int	handle_redirection(t_command *command);
void		exe_child(t_command *command, char **envp);
// static void	reset_fds(int i_stdin, int i_stdout);
int			exe_buildin(t_command *command, t_envp **envp, int *exit);
int			exe_command(t_command *command, t_envp **list, int *exit);

// token to command
int			count_commands(t_token **tokens);
int			count_args(t_token *token);
int			init_args(t_command *command, t_token **token, t_envp **envp_list);
int			init_redirection(t_token **token, t_command *command);
int			init_command(t_token **token, t_command *cmd, t_envp **envp_list);
t_command	**token_to_cmd(t_token **tokens, t_envp **envp_list);

// unset
void		unset(t_command *command, t_envp **list);

// error
void		error(int i, char *str);

#endif
