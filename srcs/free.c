/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malves-b <malves-b@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/16 14:58:39 by malves-b          #+#    #+#             */
/*   Updated: 2024/10/23 15:54:30 by malves-b         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	free_tmain(t_main *pgr)
{
	int	i;

	i = 0;
	while (pgr->tokens->next)
	{
		pgr->tokens = pgr->tokens->next;
		free (pgr->tokens->prev->content);
		free (pgr->tokens->prev);
	}
	free (pgr->tokens->content);
	free (pgr->tokens);
	free_double_array (pgr->cur_envp);
}

void	free_double_array(char **array)
{
	int	i;

	i = 0;
	while (array[i])
	{
		free(array[i]);
		i++;
	}
	free(array);
}
