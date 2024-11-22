/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pemirand <pemirand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/29 16:04:09 by pemirand          #+#    #+#             */
/*   Updated: 2024/11/21 13:14:53 by pemirand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/minishell.h"

void	print_list(t_main *pgr)
{
	printf("----------------------------------------------------\n");
	printf("| %-13s | %-8s | %-10s | %-8s |\n", "token", "id", "len token", "type");
	printf("----------------------------------------------------\n");
	for (int i = 0; i < pgr->token_amount; i++)
	{
		printf("| %-13s | %-8i | %-10i | %-8i |\n",
			pgr->tokens->content,
			pgr->tokens->id,
			pgr->tokens->c_len,
			pgr->tokens->type);

		pgr->tokens = pgr->tokens->next;
	}
	printf("----------------------------------------------------\n");
}

int	main(int argc, char *argv[], char **envp)
{
	t_main	*pgr;
	char	*line_read;
	t_token *start;

	(void)argc;
	(void)argv;
	pgr = malloc(sizeof(t_main));
	init_main(pgr, envp);
	while (1)
	{
		line_read = readline("minishell: ");
		if (!check_cmds(line_read))					/*1*/
		{
			tokenize(pgr, line_read);				/*2*/
			ft_expand(pgr); 						/*3*/

			/*------------*/
			start = pgr->tokens;
			usleep (500000);
			//print_list(pgr);
			char	**test1 = (char **)malloc(sizeof(char *)*6);
			*test1 = ft_strdup("echo");
			*(test1 + 1) = ft_strdup("hh");
			*(test1 + 2) = ft_strdup("test1");
			*(test1 + 3) = ft_strdup("test2");
			*(test1 + 4) = ft_strdup("PWD");
			*(test1 + 5) = ft_strdup("HOME");

			char	**test2 = (char **)malloc(sizeof(char *)*3);
			*test2 = ft_strdup("exit");
			*(test2 + 1) = ft_strdup("dfsd");
			*(test2 + 2) = ft_strdup("test1");

			pgr->tokens = start;
			// Test Builtins
			if (pgr->tokens->type == CMD && ft_strncmp(pgr->tokens->content, "cd", 2) == 0)
			{
				if(pgr->tokens->next)
					ft_cd(pgr->tokens->next->next->content, pgr);
				else
					ft_cd(NULL, pgr);
			} else if (pgr->tokens->type == CMD && ft_strncmp(pgr->tokens->content, "pwd", 3) == 0)
				ft_pwd();
			else if (pgr->tokens->type == CMD && ft_strncmp(pgr->tokens->content, "env", 3) == 0)
				ft_env(pgr);
			else if (pgr->tokens->type == CMD && ft_strncmp(pgr->tokens->content, "echo", 4) == 0)
				ft_echo(test1);
			else if (pgr->tokens->type == CMD && ft_strncmp(pgr->tokens->content, "unset", 5) == 0)
				ft_unset(pgr, test1);
			else if (pgr->tokens->type == CMD && ft_strncmp(pgr->tokens->content, "exit", 4) == 0)
				ft_exit(pgr, 2, test2);


			// free_tmain(pgr);
			// free (pgr);
			/*------------*/
		}
	}
	return 0;
}

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
