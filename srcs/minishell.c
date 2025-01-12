/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malves-b <malves-b@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/29 16:04:09 by pemirand          #+#    #+#             */
/*   Updated: 2025/01/12 17:06:36 by malves-b         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	g_exit = 0;

void	main_support(t_main *pgr, char *input, t_token	*start)
{
	add_history(input);
	set_exit_status(pgr);
	pgr->exit_status[1] = check_cmds(input);
	if (!pgr->exit_status[1])
	{
		tokenize(pgr, input);
		ft_expand(pgr);
		start = pgr->tokens;
		if (order_tokens(&pgr))
			return ;
		start = pgr->tokens;
		here_doc(pgr);
		if (WEXITSTATUS(g_exit) != 0)
		{
			free_tree(pgr->root);
			free_tmain(pgr, 0);
		}
		else
		{
			pgr->root = start_parsing(start);
			exec_tree(pgr->root, pgr);
			free_tree(pgr->root);
			free_tmain(pgr, 0);
		}
	}
}

int	main(int argc, char **argv, char **envp)
{
	t_main	*pgr;
	char	*input;
	t_token	*start;

	start = NULL;
	(void) argv;
	check_have_argument(argc);
	pgr = init_main(envp);
	while (1)
	{
		setup_signals();
		input = readline(SHELL_NAME);
		if (input && ft_strncmp(input, "", ft_strlen(input) != 0))
			main_support(pgr, input, start);
		if (!input)
			empty_cmd(pgr);
		free(input);
	}
	return (EXIT_SUCCESS);
}

/* ------------------------------- PRINT_LIST ------------------------------- */
// void	print_list(t_token *tokens)
// {
// 	t_token *tmp;

// 	tmp = tokens;
// 	printf("----------------------------------------------------\n");
// 	printf("| %-13s | %-8s | %-10s | %-8s |\n", "token",
// 		"id", "len token", "type");
// 	printf("----------------------------------------------------\n");
// 	while(tmp)
// 	{
// 		printf("| %-13s | %-8i | %-10i | %-8i |\n",
// 			tmp->content,
// 			tmp->id,
// 			tmp->c_len,
// 			tmp->type);

// 		tmp = tmp->next;
// 	}
// 	printf("----------------------------------------------------\n");
// }

/* -------------------------------------------------------------------------- */
/* ------------------------------- PRINT_TREE ------------------------------- */
// void	print_tree(void *root, int left, int right)
// {
// 	int		type;
// 	int		spacing;
// 	t_exec	*cmd_node;

// 	if (!root)
// 		return ;
// 	spacing = 5;
// 	type = *((int *)root);
// 	if (type == CMD)
// 	{
// 		cmd_node = (t_exec *)root;
// 		printf("%*sCMD: ", left, "");
// 		for (int i = 0; cmd_node->argv && cmd_node->argv[i]; i++)
// 			printf("%s ", cmd_node->argv[i]);
// 		printf("\n");
// 	}
// 	else if (type == REDIR || type == REDIR_MQ || type == APPEND
// 		|| type == HERE_DOC)
// 	{
// 		t_redir	*redir_node = (t_redir *)root;
// 		printf("%*s%s %s %p\n", left, "", (redir_node->type == APPEND)?
// "APPEND" :
// 			(redir_node->type == HERE_DOC)? "HERE_DOC":
// 			(redir_node->type == REDIR_MQ)? "REDIR_MQ":
// 			"REDIR" , redir_node->file, redir_node->file);
// 		printf("%*s|\n", left + spacing, "");
// 		print_tree(redir_node->next, left, right);
// 	}
// 	else if (type == PIPE)
// 	{
// 		t_pipe	*pipe_node = (t_pipe *)root;

// 		printf("%*sPIPE\n", left, "");
// 		printf("%*s/\n", left, "");
// 		print_tree(pipe_node->left, left - spacing, right);
// 		printf("%*s\\\n", left + spacing, "");
// 		print_tree(pipe_node->right, left + spacing, right);
// 	}
// }
