/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   support.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malves-b <malves-b@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/10 23:50:46 by pemirand          #+#    #+#             */
/*   Updated: 2025/01/11 14:43:17 by malves-b         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	empty_cmd(t_main *pgr)
{
	printf("exit\n");
	free_double_array(pgr->cur_envp);
	free (pgr);
	exit(0);
}

void	set_exit_status(t_main *pgr)
{
	pgr->exit_status[0] = pgr->exit_status[1];
	if (g_exit != 0)
		pgr->exit_status[0] = g_exit;
	pgr->exit_status[1] = 0;
	g_exit = 0;
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

void	free_tokens(t_token *token)
{
	t_token	*tmp;

	while (token)
	{
		tmp = token;
		token = token->next;
		if (tmp->content)
		{
			free (tmp->content);
			tmp->content = NULL;
		}
		if (tmp)
		{
			free (tmp);
			tmp = NULL;
		}
	}
}
