/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vsoulas <vsoulas@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/27 11:04:58 by vsoulas           #+#    #+#             */
/*   Updated: 2025/07/10 16:53:10 by vsoulas          ###   ########.fr       */
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

extern sig_atomic_t	g_heredoc_variable;

# define MAIN 0
# define CHILD 1

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
	int		is_out;
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

typedef struct s_export
{
	char			*name;
	char			*value;
	struct s_export	*next;
}	t_export;

// struct to keep expansion variable norminette friendly
typedef struct s_expansion
{
	int			state;
	int			i;
	int			exit;
	int			exit_stat;
	int			initial_stdin;
	int			initial_stdout;
	char		**envp;
	t_envp		*env;
	t_export	*export;
	t_command	**cmd;
	t_token		**token;
	pid_t		*pids;
}	t_expansion;

typedef struct s_exec
{
	int	i;
	int	n_cmds;
	int	pipe_fds[2];
	int	last_pipe_read;
}	t_exec;

// main
int			ft_loop(t_token **token, t_expansion *e);
int			ft_parse_input(char *in, t_expansion *e, t_token **token);
int			ft_exe(t_token **token, t_expansion *e);
void		ft_assign_types(t_token *token);

// utils pasing
int			ft_pipe_check(t_token **token);
int			ft_check_tokens(t_token **token, t_expansion *e);

// assign type
int			assign_pipe(t_token *current, int *is_cmd, int *is_red);
int			assign_redirection(t_token *current, int *is_red);
int			assign_file(t_token *current, int *is_red);
int			assign_cmd_or_arg(t_token *current, int *is_cmd, int *is_red);

// build-in
int			is_buildin(char *command);
int			exec_buildin(t_command *cmd, t_expansion *e, t_token **t);
int			env(t_command *c, t_expansion *e);
int			pwd(t_envp **env, t_command *cmd, t_expansion *e);

// cd
t_envp		*find_node_env(t_envp **list, char *name);
int			update_node_with_cwd(char *name, t_envp **envp);
int			cd(t_command *cmd, t_expansion *e);

// echo
int			echo(t_command *cmd, t_expansion *e, int fd);
int			echo_print(char *current, t_expansion *e, t_command *cmd, int fd);

// utils
int			ft_count_args(char **tokens);
char		*ft_strjoin_free(char *s1, char *s2);
int			ft_initialise_expansion(t_expansion *exp, char **env);

// utils list
int			ft_list_tokens(char **tokens, t_token **token);
t_token		*ft_new_node(char *content);
void		ft_add_last(t_token **token, t_token *node);
t_token		*ft_last(t_token **token);

// split
char		**ft_split_input(char *input, t_split *split, t_expansion *e);
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

// free e 2
void		ft_free_e(t_expansion **e);
void		ft_free_e_2(t_expansion **e);
void		ft_free_export_list(t_export **envp);

// export
int			ft_export_check(t_token **token, t_expansion *e, int fd);
int			ft_print_export(t_export **export, int fd);
int			add_export_to_envp(t_envp **env, char *value, char *name);
t_envp		*ft_new_export(char *value, char *name);
int			ft_crop(t_token *token);

// export equal
int			ft_export_equal(t_token *current, t_expansion *e);
int			ft_dollar(t_token *cur, t_variable *vari, t_expansion *e);
int			ft_replace_value_export(char *export, t_export *current);
int			ft_export_env(t_expansion *e, t_variable *vari);

// utils export
int			is_valid(t_token *cur, int fd, t_expansion *e);
int			ft_replace_value(char *export, t_envp *current);
void		ft_sort_list(t_envp **array, int total);
int			ft_compare_names(char *name1, char *name2);
void		ft_print(t_envp **list, int total, int fd);

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

// signals
int			forceout(void);
void		sig_hand(int sig);
void		parent(int sig);
void		child(int sig);
void		heredoc(int sig);

// heredoc
void		readline_here(char *delimiter, t_expansion *e);
void		ft_pid_0(int fd, char *delim, t_expansion *e, int *expand);
void		readline_cleanup(int fd, t_expansion *e, char *filename);
void		ft_heredoc(char *deli, t_expansion *e, int fd, int *expand);
int			line_read(char *delim, int fd, int expand, t_expansion *e);

// heredoc utils
int			init_pipe(int *fd);

// exit
int			ft_exit(t_expansion *e, t_command *cmd);

// commandes free
void		free_strings(t_command *command);
void		command_cleanup(t_command **commands);

// copy envp
char		*copy_str_delimiter(char *str, int check);
t_export	*new_export(char *envp);
int			add_to_envp(t_envp **envp_list, char *envp);
t_envp		*copy_envp(char **envp);

// copy export
t_export	*new_export(char *envp);
int			add_to_export(t_export **envp_list, char *envp);
t_export	*copy_export(char **envp);
int			add_export_to_export(t_export **env, char *value, char *name);
t_export	*ft_new_export_export(char *value, char *name);

// env utils
int			ft_strcmp(const char *s1, const char *s2);
char		*env_get_value(t_envp **list, char *name);
int			init_array(char **res, t_envp **list);
char		**list_to_array(t_envp **list);

// exec
int			exe_cmds(t_command **c, t_expansion *e, t_token **token);
int			pipe_init(t_exec *exec, t_expansion *e);
int			in_out_setup(t_exec *exec, t_expansion *e);
int			exec_process(t_exec *exec, t_expansion *e);

// find exec
char		*find_executable_in_path(char *command);
char		*find_executable_in_directory(char *command, char *directory);
void		free_directories(char **directories);
char		*find_executable(char *command, t_envp **envp_list);

// in out
int			input_fd(t_command *command, int i, int last_pipe_read);
int			output_fd(t_command *command, int *fd, int is_not_last);

// process
int			handle_redirection(t_command *command, t_expansion *e);
void		exe_child(t_command *c, t_expansion *e);
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
t_command	**token_to_cmd(t_token **tokens, t_expansion *e);

// unset
void		ft_name_found(t_envp *prev, t_envp **list);
void		ft_name_found_export(t_export *prev, t_export **list);
void		unset(t_command *command, t_envp **list);
void		unset_export(t_command *command, t_export **list);
void		ft_free_env(t_envp *current);
void		free_export(t_export *current);

#endif
