/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malves-b <malves-b@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/16 16:27:21 by malves-b          #+#    #+#             */
/*   Updated: 2024/11/05 16:50:39 by malves-b         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	print_list(t_main *pgr)
{
	printf("----------------------------------------------------\n");
	printf("| %-13s | %-8s | %-10s | %-8s |\n", "token", "id", "len token", "type");
	printf("----------------------------------------------------\n");
	while (pgr->tokens)
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
			puts("\nBEFORE\n");
			print_list(pgr);

			
			pgr->tokens = start;
			join_tokens(&pgr->tokens);
			puts("\n\nAFTER\n\n");
			print_list(pgr);
			// join_tokens(&pgr->tokens);
			// print_list(pgr);
			pgr->tokens = start;
			// free_tmain(pgr);
			// free (pgr);
			/*------------*/
		}
	}
	return 0;
}
