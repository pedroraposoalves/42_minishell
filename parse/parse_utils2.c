/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_utils2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malves-b <malves-b@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/29 15:17:40 by malves-b          #+#    #+#             */
/*   Updated: 2024/11/04 16:33:15 by malves-b         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

/** @brief Add a word in the (char **) */
char	**add_word(char **args, char *new_word)
{
	char	**new_args;
	int		i;

	i = 0;
	while (args[i])
		i++;
	new_args = ft_calloc(sizeof(char *), i + 2);
	if (!new_args)
		return (NULL);
	i = -1;
	while (args[++i])
	{
		new_args[i] = ft_strdup(args[i]);
		if (!new_args[i])
		{
			free_double_array(new_args);
			return (NULL);
		}
	}
	new_args[i++] = ft_strdup(new_word);
	new_args[i] = NULL;
	if (args)
		free_double_array(args);
	return (new_args);
}

/** @brief Function build multiple redir nodes*/
void	*mult_redir(t_token *start, t_token *end, char **args)
{
	t_redir	*new_redir;

	new_redir = create_redir_node();
	while (start->id < end->id)
	{
		if (start->type == CMD)
			new_redir->file = start->content;
		if (search_redir(start, end->id))
		{
			/* code */
		}
		*start = *start->next;
	}
}

void	*redir_aux(t_token *start, t_token *end, char **cmd)
{
	t_redir	*redir_node;

	if (search_redir(start->next, end->id))
		redir_node = mult_redir((*start)->next, end, cmd);
	else
	{
		while (start->id < end->id)
		{
			if (start->type == IS_SPACE)
				continue ;
			else if 
		}
	}
}