/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   join_tokens.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malves-b <malves-b@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/04 16:38:03 by malves-b          #+#    #+#             */
/*   Updated: 2024/11/05 18:39:00 by malves-b         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	iscmd_or_quotes(int type)
{
	if (type == CMD)
		return (1);
	if (type == S_QUOTES)
		return (2);
	if (type == D_QUOTES)
		return (3);
	return (0);
}

/** @brief Remove the first and last quote by the token */
void	remove_quotes(t_token **head)
{
	t_token	*cur;
	int		len;

	cur = (*head);
	while (cur != NULL)
	{
		if (cur->type == S_QUOTES || cur->type == D_QUOTES)
		{
			len = ft_strlen(cur->content);
			if (len > 1 && ((cur->content[0] == '\''
						&& cur->content[len - 1] == '\'')
					|| (cur->content[0] == '"'
						&& cur->content[len - 1] == '"')))
			{
				ft_memmove(cur->content, cur->content + 1, len - 2);
				cur->content[len - 2] = '\0';
				cur->c_len = ft_strlen(cur->content);
			}
		}
		cur = cur->next;
	}
}

/** @brief Remove the null node of the token list */
void remove_null(t_token **head)
{
    t_token *remove;
    t_token *start;
    
    start = *head;
    
    while (*head)
    {
        if ((*head)->type == IS_NULL)
        {
            // Caso 1: O nó a ser removido é o primeiro da lista
            if (!(*head)->prev)
            {
                // Mover o head para o próximo nó
                t_token *next_node = (*head)->next;
                free(*head);  // Liberar a memória do nó
                *head = next_node;  // Atualizar o head
                
                if (*head)  // Verificar se ainda há um nó na lista
                    (*head)->prev = NULL;  // Atualizar o prev do novo head
            }
            // Caso 2: O nó a ser removido é o último da lista
            else if (!(*head)->next)
            {
                remove = *head;
                (*head)->prev->next = NULL;  // Atualizar o próximo do nó anterior
                free(remove);  // Liberar a memória do nó
                *head = NULL;  // Não há mais nós
            }
            // Caso 3: O nó a ser removido está no meio da lista
            else
            {
                remove = *head;
                (*head)->prev->next = (*head)->next;  // Atualizar o próximo do nó anterior
                (*head)->next->prev = (*head)->prev;  // Atualizar o anterior do nó seguinte
                free(remove);  // Liberar a memória do nó
                *head = (*head)->next;  // Continuar com o próximo nó
            }
        }
        else
        {
            // Se não foi removido, mover para o próximo nó
            *head = (*head)->next;
        }
    }
    // Restaurar o head para o início da lista, se necessário
    *head = start;  // Se precisar retornar ao início, pode ser removido se não necessário
}

void	join_tokens(t_token **tk)
{
	t_token	*remove;
	t_token	*start;

	start = *tk;
	remove_quotes(tk);
	remove_null(tk);
	while (*tk && (*tk)->next)
	{
		if (iscmd_or_quotes((*tk)->type)
			&& iscmd_or_quotes((*tk)->next->type))
		{
			(*tk)->content = ft_strjoin((*tk)->content, (*tk)->next->content);
			(*tk)->c_len = ft_strlen((*tk)->content);
			remove = (*tk)->next;
			(*tk)->next = (*tk)->next->next;
			if ((*tk)->next)
				(*tk)->next->prev = (*tk);
			free (remove);
		}
		if ((*tk)->next)
			(*tk) = (*tk)->next;
		else
			break ;
	}
	(*tk) = start;
}
