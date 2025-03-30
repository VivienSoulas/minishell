/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdavtian <jdavtian@student.codam.nl>       +#+  +:+       +#+        */
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

// main
int			ft_loop(int *exit_stat, t_token **token, t_envp **env, int *exit_c);
int			ft_parse_input(char *in, t_envp **env, int *exit, t_token **token);
void		ft_assign_types(t_token *token);
int			ft_check_tokens(t_token **token);

// variable expansion
int			ft_dollar_sign(t_token *to, t_envp **env);
int			ft_double_quote_expand(t_token *to, t_envp **env);
int			ft_single_quote_expand(t_token *to, t_envp **env);

// utils
int			ft_count_args(char **tokens);
void		handler(int sig);
void		signals_handling(void);

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
int			ft_export_check(t_envp **env, t_token **token);
int			add_export_to_envp(t_envp **env, char *export);
int			ft_print_export(t_envp **env);
void		ft_sort_list(t_envp **array, int total);
int			ft_compare_names(char *name1, char *name2);

// utils export
int			ft_replace_value(char *export, t_envp *current);
int			is_valid(char *str);
void		ft_print(t_envp **list, int total);

// variable expansion
int			ft_variable_expansion(t_token **token, t_envp **env);
int			ft_dollar_sign(t_token *to, t_envp **env);
int			ft_double_quote_expand(t_token *to, t_envp **env);
int			ft_single_quote_expand(t_token *to, t_envp **env);

// build-in
int			is_buildin(char *command);
int			exec_buildin(t_command *cmd, t_envp **envp, int *exit);
void		env(t_envp **env);
void		pwd(t_envp **env);
void		echo(t_command *command, t_envp **env);

// utils build-in
int			ft_check_invalid(char *arg, t_envp **env);

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
