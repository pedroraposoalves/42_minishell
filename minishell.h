/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malves-b <malves-b@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/11 15:30:03 by malves-b          #+#    #+#             */
/*   Updated: 2024/10/16 11:00:39 by malves-b         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL
# define MINISHELL

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
// # define EXP$ 9 /*---*/
// # define NULL 9 /*---*/

/* -------------------------------------------------------------------------- */
/*                                  TOKENIZE                                  */
/* -------------------------------------------------------------------------- */

int		is_special_char(char c);
int		ft_isspace(int c);
int		get_token_amount(char *cmd);
char	**tokenize_aux(char *cmd);

/* -------------------------------------------------------------------------- */

typedef struct s_token
{
	char            *content;
	int             id;
	int             type;
	int             c_len;
	struct s_token  *prev;
	struct s_token  *next;
} t_token ;

typedef	struct	s_main
{
	int             token_amount;
	struct s_token  *tokens;
	char			**envp;
} t_main;

// typedef struct s_pipe
// {
//     char    *left;
//     char    *right;
// } t_pipe;

// typedef struct s_redir
// {
//     char    *file;
//     char    *next;
// } t_redir;

#endif