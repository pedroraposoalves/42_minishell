/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malves-b <malves-b@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/29 16:04:09 by pemirand          #+#    #+#             */
/*   Updated: 2025/01/09 16:11:27 by pemirand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	global_exit = 0;

void	set_exit_status(t_main *pgr)
{
	pgr->exit_status[0] = pgr->exit_status[1];
	if (global_exit != 0)
		pgr->exit_status[0] = global_exit;
	pgr->exit_status[1] = 0;
	global_exit = 0;
}

void	check_have_argument(int argc)
{
	if (argc != 1)
	{
		print_error(SHELL_NAME, "The minishell should'nt have arguments!",
			NULL, NULL);
		exit (127);
	}
}

void	print_list(t_main *pgr);

int	main(int argc, char **argv, char **envp)
{
	t_main	*pgr;
	char	*input;
	t_token	*start;

	(void) argv;
	pgr = init_main(envp);
	check_have_argument(argc);
	while (1)
	{
		setup_signals();
		input = readline(SHELL_NAME);
		if (input && ft_strncmp(input, "", ft_strlen(input) != 0))
		{
			add_history(input);
			set_exit_status(pgr);
			if (!(pgr->exit_status[1] = check_cmds(input)))
			{
				tokenize(pgr, input);
				ft_expand(pgr);
				start = pgr->tokens;
				if (order_tokens(&pgr))
					continue;
				start = pgr->tokens;
				here_doc(pgr);
				pgr->root = start_parsing(start);
				exec_tree(pgr->root, pgr);
				free_tree(pgr->root);
				free_tmain(pgr, 0);
			}
		}
		if (!input)
		{
			puts("exit");
			return (0);
		}
		free(input);
	}
	return (EXIT_SUCCESS);
}

/* ------------------------------- PRINT_LIST ------------------------------- */
void	print_list(t_token *tokens)
{
	t_token *tmp;

	tmp = tokens;
	printf("----------------------------------------------------\n");
	printf("| %-13s | %-8s | %-10s | %-8s |\n", "token",
		"id", "len token", "type");
	printf("----------------------------------------------------\n");
	while(tmp)
	{
		printf("| %-13s | %-8i | %-10i | %-8i |\n",
			tmp->content,
			tmp->id,
			tmp->c_len,
			tmp->type);

		tmp = tmp->next;
	}
	printf("----------------------------------------------------\n");
}

/* -------------------------------------------------------------------------- */
/* ------------------------------- PRINT_TREE ------------------------------- */
void	print_tree(void *root, int left, int right)
{
	int		type;
	int		spacing;
	t_exec	*cmd_node;

	if (!root)
		return ;
	spacing = 5;
	type = *((int *)root);
	if (type == CMD)
	{
		cmd_node = (t_exec *)root;
		printf("%*sCMD: ", left, "");
		for (int i = 0; cmd_node->argv && cmd_node->argv[i]; i++)
			printf("%s ", cmd_node->argv[i]);
		printf("\n");
	}
	else if (type == REDIR || type == REDIR_MQ || type == APPEND
		|| type == HERE_DOC)
	{
		t_redir	*redir_node = (t_redir *)root;
		printf("%*s%s %s %p\n", left, "", (redir_node->type == APPEND)? "APPEND" :
			(redir_node->type == HERE_DOC)? "HERE_DOC":
			(redir_node->type == REDIR_MQ)? "REDIR_MQ":
			"REDIR" , redir_node->file, redir_node->file);
		printf("%*s|\n", left + spacing, "");
		print_tree(redir_node->next, left, right);
	}
	else if (type == PIPE)
	{
		t_pipe	*pipe_node = (t_pipe *)root;

		printf("%*sPIPE\n", left, "");
		printf("%*s/\n", left, "");
		print_tree(pipe_node->left, left - spacing, right);
		printf("%*s\\\n", left + spacing, "");
		print_tree(pipe_node->right, left + spacing, right);
	}
}
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
// 		printf("%*s%s %s\n", left, "", (redir_node->type == APPEND)? "APPEND" :
// 			(redir_node->type == HERE_DOC)? "HERE_DOC":
// 			(redir_node->type == REDIR_MQ)? "REDIR_MQ":
// 			"REDIR" , redir_node->file);
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
// int	main(int argc, char *argv[], char **envp)
// {
// 	t_main	*pgr;
// 	char	*line_read;
// 	t_token *start;

// 	(void)argc;
// 	(void)argv;
// 	pgr = malloc(sizeof(t_main));
// 	init_main(pgr, envp);
// 	while (1)
// 	{
// 		line_read = readline("minishell: ");
// 		if (!check_cmds(line_read))					/*1*/
// 		{
// 			tokenize(pgr, line_read);				/*2*/
// 			ft_expand(pgr); 						/*3*/

// 			/*------------*/
// 			start = pgr->tokens;
// 			usleep (500000);
// 			//print_list(pgr);
// 			char	**test1 = (char **)malloc(sizeof(char *)*6);
// 			*test1 = ft_strdup("echo");
// 			*(test1 + 1) = ft_strdup("hh");
// 			*(test1 + 2) = ft_strdup("test1");
// 			*(test1 + 3) = ft_strdup("test2");
// 			*(test1 + 4) = ft_strdup("PWD");
// 			*(test1 + 5) = ft_strdup("HOME");

// 			char	**test2 = (char **)malloc(sizeof(char *)*3);
// 			*test2 = ft_strdup("exit");
// 			*(test2 + 1) = ft_strdup("dfsd");
// 			*(test2 + 2) = ft_strdup("test1");

// 			char	**test3 = (char **)malloc(sizeof(char *)*5);
// 			*test3 = ft_strdup("export");
// 			*(test3 + 1) = ft_strdup("dfsd");
// 			*(test3 + 2) = ft_strdup("3ed");
// 			*(test3 + 3) = ft_strdup("5ff");
// 			*(test3 + 4) = ft_strdup("fsdfds=tetete");

// 			pgr->tokens = start;
// 			// Test Builtins
// 			if (pgr->tokens->type == CMD
//	 			&& ft_strncmp(pgr->tokens->content, "cd", 2) == 0)
// 			{
// 				if(pgr->tokens->next)
// 					ft_cd(pgr->tokens->next->next->content, pgr);
// 				else
// 					ft_cd(NULL, pgr);
// 			} else if (pgr->tokens->type == CMD
//				&& ft_strncmp(pgr->tokens->content, "pwd", 3) == 0)
// 				ft_pwd();
// 			else if (pgr->tokens->type == CMD
//				&& ft_strncmp(pgr->tokens->content, "env", 3) == 0)
// 				ft_env(pgr);
// 			else if (pgr->tokens->type == CMD
//				&& ft_strncmp(pgr->tokens->content, "echo", 4) == 0)
// 				ft_echo(test1);
// 			else if (pgr->tokens->type == CMD
//				&& ft_strncmp(pgr->tokens->content, "unset", 5) == 0)
// 				ft_unset(pgr, test1);
// 			else if (pgr->tokens->type == CMD
//				&& ft_strncmp(pgr->tokens->content, "exit", 4) == 0)
// 				ft_exit(pgr, 2, test2);
// 			else if (pgr->tokens->type == CMD
//				&& ft_strncmp(pgr->tokens->content, "export", 4) == 0)
// 				ft_export(pgr, 5, test3);
// 			// free_tmain(pgr);
// 			// free (pgr);
// 			/*------------*/
// 		}
// 	}
// 	return 0;
// }

/* int	main(int argc, char **argv, char **env)
{
	if (argc == 4)
	{
		char s[100];
		printf("%s -> %s\n", argv[2], get_env_value(argv[2], env));
		printf("%s -> %s\n", argv[3], get_env_value(argv[3], env));
		printf("%d\n", ft_cd(argv[1], env));
		printf("%s\n", getcwd(s, 100));
	}

	return (0);
} */
