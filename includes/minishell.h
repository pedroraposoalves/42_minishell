/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pemirand <pemirand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/11 15:30:03 by malves-b          #+#    #+#             */
/*   Updated: 2025/01/08 15:29:08 by pemirand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <fcntl.h>
# include <signal.h>
# include <sys/wait.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <ctype.h>
# include <errno.h>
# include <limits.h>
# include <string.h>
# include "libft.h"

# define PIPE 1
# define REDIR 2
# define CMD 3
# define IS_SPACE 4
# define S_QUOTES 5
# define D_QUOTES 6
# define APPEND 7
# define HERE_DOC 8
# define IS_NULL 9
# define REDIR_MQ 10

extern int	global_exit;

# define SHELL_NAME "minishell: "

typedef struct s_token
{
	char			*content;
	int				id;
	int				type;
	int				c_len;
	struct s_token	*prev;
	struct s_token	*next;
}	t_token;

typedef struct s_main
{
	int				token_amount;
	int				exit_status[2];
	struct s_token	*tokens;
	char			**cur_envp;
	void			*root;
}	t_main;

/* ------------------------------ TREE STRUCTS ------------------------------ */

typedef struct s_exec
{
	int		type;
	char	**argv;
}	t_exec;

typedef struct s_redir
{
	int		type;
	char	*file;
	void	*next;
}	t_redir;

typedef struct s_pipe
{
	int		type;
	void	*left;
	void	*right;
}	t_pipe;

/* -------------------------------- BUILTINS -------------------------------- */

int		ft_cd(char *path, t_main *pgr);
int		ft_env(t_main *pgr);
int		update_pwd(t_main *pgr, char *old_cwd);
int		ft_echo(char **argv);
int		ft_pwd(void);
int		ft_unset(t_main *pgr, char **argv);
int		ft_exit(t_main *pgr, int argc, char **argv, void *root);
int		ft_export(t_main *pgr, char **argv);

/* ------------------------------ ENV FUNCTIONS ----------------------------- */

char	*get_env_value(char *value, t_main *pgr);
int		set_env_value(char *variable, t_main *pgr, char *new_v);
int		append_env_value(char *variable, t_main *pgr);
int		del_env_value(char *value, t_main *pgr);
int		cmp_env(char *s1, char *s2);
char	*remove_badenvp(char **str, int j);

/* ---------------------------------- EXEC ---------------------------------- */

void	ft_redir(void *node, t_main *pgr);
void	ft_exec(void *node, t_main *pgr, int status);
void	exec_tree(void *root, t_main *pgr);
int		ft_execve(t_exec *exec_node, char **envp);
char	*find_path(char *cmd, char **envp);
int		isbuiltin(char *str);
int		call_builtin(int number, t_exec *node, t_main *pgr, void *root);

/* --------------------------------- HEREDOC -------------------------------- */

int	here_doc(t_token *list);

/* ---------------------------------- INIT ---------------------------------- */

void	*start_parsing(t_token *start);
t_main	*init_main(char **envp);
t_exec	*create_exec_node(void);
t_redir	*create_redir_node(int type);
t_pipe	*create_pipe_node(void);
void	add_node(t_token **current, char *token);

/* --------------------------------- PARSING -------------------------------- */

int		check_cmds(char *cmd);
void	tokenize(t_main *pgr, char *cmd);
int		is_special_char(char c);
int		ft_isspace(int c);
int		get_token_amount(char *cmd);
char	**tokenize_aux(char *cmd);
int		check_isjoin(char *cmd, int *error);
void	get_exit_status(char **content, int ret_last_cmd);
void	change_content(char *vrbl, char **content, int *i, int word_len);
void	set_envp_value(char **cont, char **envp, int i, int wrd);
int		search_exp(char *content);
void	ft_expand(t_main *main);
int		search_pipe(t_token **token, int limit);
int		search_redir(t_token **token, int limit);
char	**add_word(char **args, char *new_word);
t_redir	*redir_aux(t_token **start, t_exec *exec_node);
int		join_tokens(t_token **tk, t_token *remove, t_token *start, char *aux);
int		token_type(char *token);
int		special_or_space(char *cmd, int *i, int *amount);
int		is_quote(char *cmd, int *i, int *amount);
t_pipe	*parse_pipe(t_token **start, t_token **cur, t_token *ptr_aux);
int		order_tokens(t_main **pgr);
int		check_dir_after_redir(const char *cmd);

/* --------------------------------- SIGNALS -------------------------------- */

void	setup_signals(void);

/* -----------------------------------UTILS---------------------------------- */

void	free_tmain(t_main *pgr, int exit_flag);
void	free_double_array(char **array);
int		free_all(t_main *pgr, void *root, int exit_flag);
void	free_tree(void *root);
int		print_error(char *s1, char *s2, char *s3, char *message);
int		print_error_errno(char *s1, char *s2, char *s3);
char	**ft_sort_char_tab(char **tab, int size);
char	**matrix_dup(char **m);
void	free_matrix(char **m);
int		ft_str_char(char *s, char c);
int		matrix_len(char **m);
int		set_exit_signal(int exit_status);

/* -----------------------------------DEBUG---------------------------------- */

void	print_list(t_token *tokens);
void	print_tree(void *root, int left, int right);

#endif
