/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malves-b <malves-b@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/16 16:27:21 by malves-b          #+#    #+#             */
/*   Updated: 2024/11/06 16:42:12 by malves-b         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

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
			puts("\nBEFORE\n");
			print_list(pgr);

			
			pgr->tokens = start;
			join_tokens(&pgr->tokens);
			puts("\n\nAFTER\n\n");
			print_list(pgr);
			pgr->tokens = start;

			puts("\n\nTREE :\n\n");
			void *root = start_parsing(start);
			print_tree(root, 40, 40);
			// free_tmain(pgr);
			// free (pgr);
			/*------------*/
		}
	}
	return 0;
}
