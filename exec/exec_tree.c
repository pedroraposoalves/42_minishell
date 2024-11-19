/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_tree.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malves-b <malves-b@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/13 17:42:58 by malves-b          #+#    #+#             */
/*   Updated: 2024/11/19 14:11:44 by malves-b         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	exec_tree(void *root)
{
	int	type;

	type = *((int *)root);
	if (type == PIPE)
	{
		/* code */
	}
	else if (type == CMD)
	{
		/* code */
	}
	else
	{
		/* code */
	}
}

