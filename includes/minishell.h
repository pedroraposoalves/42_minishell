/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pemirand <pemirand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/11 15:30:03 by malves-b          #+#    #+#             */
/*   Updated: 2024/11/22 09:42:13 by pemirand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <fcntl.h>
# include <string.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <ctype.h>
# include <errno.h>
# include <limits.h>
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

# define SHELL_NAME "minishell"

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
	int				return_last_cmd;
	int				return_cur_cmd;
	struct s_token	*tokens;
	char			**cur_envp;
}	t_main;

/* ------------------------------ TREE STRUCTS ------------------------------ */

typedef struct s_exec
{
	int		type;
	char	**args;
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

/* -------------------------------------------------------------------------- */
/*                                  TOKENIZE                                  */
/* -------------------------------------------------------------------------- */

void	tokenize(t_main *pgr, char *cmd);
int		is_special_char(char c);
int		ft_isspace(int c);
int		get_token_amount(char *cmd);
char	**tokenize_aux(char *cmd);

/* -------------------------------------------------------------------------- */
/*                                    FREE                                    */
/* -------------------------------------------------------------------------- */

void	free_tmain(t_main *pgr);
void	free_double_array(char **array);
void	free_all(t_main *pgr, void *root);

/* -------------------------------------------------------------------------- */

void	init_main(t_main *pgr, char **envp);
int		check_cmds(char *cmd);
int		check_isjoin(char *cmd, int *error);
void	print_err(char *message);

/* -------------------------------------------------------------------------- */
/*                                   EXPAND                                   */
/* -------------------------------------------------------------------------- */

void	get_return_last_cmd(char **content, int ret_last_cmd);
void	change_content(char *vrbl, char **content, int *i, int word_len);
void	set_envp_value(char **cont, char **envp, int i, int wrd);
int		search_exp(char *content);
void	ft_expand(t_main *main);


int		cmp_env(char *s1, char *s2);
void	remove_badenvp(char **str, int i, int j);

/* -------------------------------------------------------------------------- */
/*                                 CREATE TREE                                */
/* -------------------------------------------------------------------------- */

void	*start_parsing(t_token *start);

// --- UTILS --- //
int		search_pipe(t_token **token, int limit);
int		search_redir(t_token **token, int limit);
t_exec	*create_exec_node(void);
t_redir	*create_redir_node(void);
t_pipe	*create_pipe_node(void);
char	**add_word(char **args, char *new_word);
t_redir	*redir_aux(t_token **start, t_exec *exec_node);
char	*find_path(char *cmd, char **envp);
int		isbuiltin(char *str);
void	join_tokens(t_token **tokens);

/* ---------------------------------- EXEC ---------------------------------- */

void	ft_redir(void *node, t_main *pgr);
void	exec_tree(void *root, t_main *pgr);
int		ft_execve(t_exec *exec_node, char **envp);
void	ft_exec(void *node, t_main *pgr);

/* --------------------------------- SIGNALS -------------------------------- */

void	setup_signals(void);

/* --------------------------- DEBUG AUX FUNCTIONS -------------------------- */

void	print_list(t_main *pgr);
void	print_tree(void *root, int left, int right);

/* ------------------------------ ENV FUNCTIONS ----------------------------- */

char	*get_env_value(char *value, t_main *pgr);
int		set_env_value(char *variable, t_main *pgr, char *new_v);
int		append_env_value(char *variable, t_main *pgr);
int		del_env_value(char *value, t_main *pgr);

/* -------------------------------- BUILTINS -------------------------------- */
int		ft_cd(char *path, t_main *pgr);
int		ft_env(t_main *pgr);
int		update_pwd(t_main *pgr, char *old_cwd);
int		ft_echo(char **argv);
int		ft_pwd(void);
int		ft_unset(t_main *pgr, char **argv);
int		ft_exit(t_main *pgr, int argc, char **argv);

/* ----------------------------- ERROR HANDLING ----------------------------- */

int		print_error(char *s1, char *s2, char *s3, char *message);
int		print_error_errno(char *s1, char *s2, char *s3);

/* -------------------------------------------------------------------------- */
#endif
