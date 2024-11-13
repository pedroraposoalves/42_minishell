/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malves-b <malves-b@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/16 16:27:21 by malves-b          #+#    #+#             */
/*   Updated: 2024/11/13 17:15:59 by malves-b         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	g_signal;

int	main(int argc, char *argv[], char **envp)
{
	t_main	*pgr;
	char	*input;
	t_token *start;

	(void)argc;
	(void)argv;
	pgr = malloc(sizeof(t_main));
	init_main(pgr, envp);
	while (1)
	{
		input = readline("minishell: ");
		if (input)
			add_history(input);
		if (argc != 1)
		{
			print_err ("The minishell should not have aguments!");
			return (127);
		}
		if (!check_cmds(input))					/*1*/
		{
			tokenize(pgr, input);				/*2*/
			ft_expand(pgr); 						/*3*/
			
			/*------------*/
			start = pgr->tokens;
			join_tokens(&pgr->tokens);
			puts("\nTOKEN LIST:\n");
			print_list(pgr);
			pgr->tokens = start;

			puts("\n\nTREE :\n\n");
			void *root = start_parsing(start);
			print_tree(root, 40, 40);
			// free_all(pgr, root);
			/*------------*/
		}
	}
	return 0;
}
