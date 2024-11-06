/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malves-b <malves-b@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/11 15:30:03 by malves-b          #+#    #+#             */
/*   Updated: 2024/11/06 16:44:51 by malves-b         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <readline/readline.h>
# include <readline/history.h>
# include "libft/libft.h"

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

/* -------------------------------------------------------------------------- */

void	init_main(t_main *pgr, char **envp);
int		check_cmds(char *cmd);
int		check_isjoin(char *cmd, int *error);

/* -------------------------------------------------------------------------- */
/*                                   EXPAND                                   */
/* -------------------------------------------------------------------------- */
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
t_redir	*redir_aux(t_token **start, t_token *end, t_exec *exec_node);

void	join_tokens(t_token **tokens);

/* -------------------------------------------------------------------------- */


/* --------------------------- DEBUG AUX FUNCTIONS -------------------------- */

void	print_list(t_main *pgr);
void	print_tree(void *root, int left, int right);

/* -------------------------------------------------------------------------- */

#endif