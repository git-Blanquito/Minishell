/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: almorene <almorene@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/22 02:41:00 by aial              #+#    #+#             */
/*   Updated: 2025/11/25 20:29:26 by almorene         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "libft.h"
# include <fcntl.h>
# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <limits.h>
# include <stdarg.h>
# include <signal.h>
# include <sys/wait.h>
# include <sys/stat.h>
# include <errno.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <termios.h>

typedef struct s_line	t_line;
typedef struct s_token	t_token;

typedef enum e_token_type
{
	TOKEN_WORD,
	TOKEN_PIPE,
	TOKEN_REDIR_IN,
	TOKEN_REDIR_OUT,
	TOKEN_APPEND,
	TOKEN_HEREDOC,
	TOKEN_STRING
}	t_token_type;

typedef struct s_token
{
	t_token_type		type;
	char				*value;
	int					was_single_quoted;
	int					was_double_quoted;
	t_line				*line;
	struct s_token		*next;
}	t_token;

typedef struct s_redir
{
	t_token_type		type;
	char				*filename;
	char				*delimiter;
	int					expand_vars;
	struct s_redir		*next;
}	t_redir;

typedef struct s_args
{
	char				*value;
	int					was_single_quoted;
	int					was_double_quoted;
}	t_args;

typedef struct s_local_var
{
	char				*name;
	char				*value;
	struct s_local_var	*next;
}	t_local_var;

typedef struct s_cmd
{
	t_args				**argv;
	t_redir				*redirs;
	int					error;
	struct s_cmd		*next;
}	t_cmd;

typedef struct s_line
{
	t_cmd				*cmds;
	t_token				*tokens;
	t_local_var			*local_vars;
	char				**g_environ;
}	t_line;

typedef struct s_exp_ctx
{
	t_line				*line;
	int					last_status;
	int					was_single_quoted;
	int					was_double_quoted;
	char				**envp;
	char				*out;
}	t_exp_ctx;

typedef struct s_quote_ctx
{
	int					*was_single;
	int					*was_double;
	char				*input;
	t_token				**head;
	t_line				*line;
}	t_quote_ctx;

typedef struct s_pipe_ctx
{
	int					in_fd;
	int					fd[2];
	pid_t				pids[1024];
	int					pid_count;
}	t_pipe_ctx;

typedef struct s_word_args
{
	char				*input;
	size_t				*i;
	int					last_status;
	t_line				*line;
}	t_word_args;

typedef struct s_hdctx
{
	int					interrupted;
	int					expand_vars;
	char				*delim;
	t_line				*line;
}	t_hdctx;

extern int				g_last_status;

void		print_token(t_token *head);
void		print_commands(t_cmd *cmds);

//free() de main
void		free_token(t_token *head);
void		free_redirs(t_redir *redir);
void		free_argv(t_args **argv);
void		free_argv2(char **argv);
void		free_argv3(char **argv, char *str);
void		free_commands(t_cmd *cmds);
void		free_main_mem(t_token *head, t_cmd *cmds, char	*input);

//main
int			copy_env_values(char **envp, int count, t_line *line);
int			dup_env(char **envp, t_line *line);
void		line_comander(t_line *line, char *input, int *last_status);
void		cleanup_and_exit(int last_status, t_line *line);
int			init_env(char **envp, t_line *line);
int			is_only_white_space(char *str);

//signals
void		setup_signals_parent(void);
void		setup_signals_exec(void);
void		setup_signals_prompt(void);
void		sigint_handler_prompt(int signo);
void		sigint_handler_prompt2(int signo);
void		setup_signals_heredoc(void);
void		restore_signals_heredoc(void);
void		sigint_handler_heredoc(int sig);
void		hd_setup_signals(void);
void		disable_echoctl(void);
void		enable_echoctl(void);

//tokenize
t_token		*tokenize(char *input, int last_status, t_line *line);
t_token		*token_new(t_token_type type, char *value,
				int was_single_quoted, int was_double_quoted);
void		token_add_back(t_token **list, t_token *new);
void		add_double_operator_token(t_token **head,
				char *value, size_t *i, char *input);
void		add_simple_operator_token(t_token **head,
				char *value, size_t *i, char *input);
int			is_operator(char c);
int			is_space(char c);
void		skip_spaces(char *input, size_t *i);
char		*process_unquoted(char *input, size_t *i);
void		create_and_add_token(t_quote_ctx *ctx,
				char *token_str, int was_single, int was_double);
void		handle_word(t_token **head, t_word_args args);
char		*strjoin_free(char *s1, char *s2);
char		*process_quoted(size_t *i, t_quote_ctx ctx,
				int *out_was_single, int *out_was_double);
void		process_word_loop(size_t *i, t_quote_ctx ctx,
				char **token_str, int last_status);
char		*expand_if_needed(char *part,
				int part_single, int last_status, t_quote_ctx *ctx);
int			handle_redirects(t_token **head, char *input, size_t *i);

//parse_tokens
t_cmd		*parse_tokens(t_token *tokens);
t_cmd		*cmd_new(void);
t_redir		*redir_new(t_token_type type, char *filename);
void		cmd_add_argv(t_cmd *cmd, t_token *tok);
void		cmd_add_redir(t_cmd *cmd, t_token_type type, char *filename);
t_args		*new_arg(const char *word, int was_single_quoted,
				int was_double_quoted);
t_token		*parse_token_type(t_token *tok, t_cmd **curr,
				int *g_heredoc_index, t_cmd **head);
int			parse_heredoc(t_token **tokt_cmd, t_cmd *cmd, int *g_heredoc_index);
t_token		*parse_redir(t_token *tok, t_cmd *cmd);
t_token		*handle_word_or_string(t_token *tok, t_cmd **curr);
t_token		*handle_heredoc(t_token *tok, t_cmd *curr, int *g_heredoc_index);
t_token		*handle_redir(t_token *tok, t_cmd *curr);
int			is_single_quoted(const char *s);
int			get_expand_flag(t_token *next);

//print_errors
void		print_exit_error(char *str);
void		free_token_list(t_token *head);
void		exit_malloc_error_tokens(t_token **head);
void		exit_malloc_error_tokens_input(t_token **head, char *input);
void		*error_malloc(void);

//expand tokneize
char		*get_env_value3(char *name);
char		*expand_variables(const char *s, int last_status, t_line *line);
char		*expand_variables_heredoc(const char *s,
				int last_status, char **envp);
//expanse utils1
char		*expand_str(const char *s, t_exp_ctx *ctx);
const char	*expand_char(const char *p, t_exp_ctx *ctx);
const char	*expand_variable(const char *p, t_exp_ctx *ctx);
const char	*expand_name_var(const char *p, t_exp_ctx *ctx);
const char	*expand_last_status(const char *p, t_exp_ctx *ctx);
//expanse utils2
const char	*expand_dollar_end(const char *p, t_exp_ctx *ctx);
int			expand_home(const char *s, const char *p, t_exp_ctx *ctx);
char		*append_ch(char *s, char c);
char		*append_str(char *s, const char *t);
//expanse utils3
char		*itoa_status(int n);
char		*xstrdup(const char *s);
int			is_name_char(int c);
int			is_name_start(int c);

//local_variable
void		set_local_var(t_line *line, char *name, char *value);
char		*get_var(t_line *line, char *name, char **envp);
char		*env_get(char *name, char **envp);

//Execute
//int			is_builtin(char *cmd);
int			exec_builtin(t_cmd *cmd, int last_status, t_line *line);
char		*find_executable(char *cmd, t_line *line);
int			exec_external(t_cmd *cmd, t_line *line);
void		handle_child_signal(int status);
int			get_exit_status_from_wait(int status);
int			execute_command(t_cmd *cmd,
				int last_status, t_line *line);
int			builtin_cd(char **args, t_line *line);
int			env_index2(const char *name, t_line *line);
char		*get_env_value2(const char *name, t_line *line);
int			cd_error(const char *msg);
char		*create_env_entry(const char *name, const char *value);
void		update_existing_env(t_line *line, char *entry, int idx);
void		add_new_env_entry(t_line *line, char *entry);
char		*get_cd_target(char **args, char *oldpwd, t_line *line);
void		update_env_var(const char *name, const char *value, t_line *line);
int			builtin_echo(char **args);
int			builtin_pwd(t_line *line);
char		*get_env_value5(const char *name, t_line *line);
char		*get_env_value6(const char *name, char **envp);
int			builtin_exit(char **args, int last_status);
int			builtin_export(char **args, t_line *line);
int			builtin_unset(char **args, t_line *line);
int			builtin_env(t_line *line);
int			is_builtin(char *cmd);
int			env_index(char *name, t_line *line);
//Execute utils1
int			handle_assignment_if_needed(t_cmd *cmd, t_line *line, int i);
int			exec_builtin_dispatch(t_cmd *cmd,
				int last_status, t_line *line, int i);
int			exec_external_dispatch(t_cmd *cmd, int i, t_line *line);
//Execute utils2
void		exec_child_process(t_cmd *cmd, t_line *line);
void		handle_execve_error(char **argv_c, char *path);
int			is_directory(const char *path);
void		write_error(const char *s1, const char *s2, const char *s3);
//Execute utils3
char		*search_in_dirs(char **dirs, char *cmd);
char		*get_path_from_env(t_line *line);
int			exec_shell_builtin_with_redirs(t_cmd *cmd,
				int last_status, t_line *line);
//Execute utils4
int			save_stdio(int *saved_stdin, int *saved_stdout);
int			restore_stdio(int saved_stdin, int saved_stdout);
int			exec_builtin_in_child(t_cmd *cmd, int last_status, t_line *line);
int			is_shell_builtin(const char *name);
//Execute utils5
int			is_assignment(const char *s);
char		**args_to_argv(t_args **args);

//pipex y redir
int			execute_pipeline(t_cmd *cmds, t_line *line);
int			apply_redirections(t_redir *rlist);
char		*create_heredoc(const char *delimiter,
				int index, int expand_vars, t_line *line);
void		handle_malloc_error(t_token *head,
				t_cmd *cmds, char *input, t_redir *redirs);
//pipex_utils1
void		parent_post_fork(t_pipe_ctx *ctx, pid_t pid, int has_next);
void		cleanup_pipeline_heredocs(t_line *line);
int			wait_all_children(pid_t *pids, int count);
pid_t		spawn_child(t_cmd *cmd, int *fd);
void		child_execute_cmd(t_cmd *cmd,
				int last_status, t_line *line);
//pipex_utils2
void		child_setup_io(t_cmd *cmd, int in_fd, int *fd);
int			open_and_dup(const char *file, int flags, int mode, int dest_fd);
void		replace_dollar_status(t_args **argv, int last_status);
//pipex_utils3
void		child_heredoc(const char *filename,
				const char *delimiter, int expand_vars, t_line *line);
//void		write_heredoc_loop(int fd, const char *delim,
				//int expand_vars, t_line *line, t_hdctx *ctx);
void		write_heredoc_loop(int fd, t_hdctx *ctx);
char		*gen_heredoc_filename(int index);
char		**build_execve_argv(t_args **args);
char		*expand_heredoc_line(const char *line, int last, t_line *pline);
//pipex_utils4
int			count_args(t_args **argv);
void		cleanup_heredocs(t_redir *rlist);
char		*handle_single_quotes(const char *line, size_t *i);
char		*handle_single_quotes2(const char *line, size_t *i,
				int last_status, t_token **head);
char		*handle_double_quotes2(const char *line, size_t *i,
				int last_status, t_token **head);
char		*process_raw_segment(const char *line, size_t *i,
				int last, t_line *pline);

//export
char		*looking_in_local_vars(char *name, t_line *line);
int			names_match(char *a, char *b);
t_local_var	*find_local_var(char *name, t_local_var *vars);
void		sort_env(char **arr, int n);
int			env_count(t_line *line);
int			is_valid_name(char *name);
int			export_print_env(t_line *line);
int			export_set_env(char *name, char *full_entry, t_line *line);

#endif
