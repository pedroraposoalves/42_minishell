/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenize.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malves-b <malves-b@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/15 11:02:56 by malves-b          #+#    #+#             */
/*   Updated: 2024/11/20 16:53:05 by malves-b         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	token_type(char *token)
{
	if (token[0] == '|')
		return (PIPE);
	else if (!ft_strncmp(token, ">>", 2))
		return (APPEND);
	else if (!ft_strncmp (token, "<<", 2))
		return (HERE_DOC);
	else if (token[0] == '>')
		return (REDIR);
	else if (token[0] == '<')
		return (REDIR_MQ);
	else if (ft_isspace(token[0]))
		return (IS_SPACE);
	else if (!ft_strncmp(token, "\"\"", ft_strlen(token)))
		return (IS_NULL);
	else if (!ft_strncmp(token, "\'\'", ft_strlen(token)))
		return (IS_NULL);
	else if (token[0] == '\'')
		return (S_QUOTES);
	else if (token[0] == '"')
		return (D_QUOTES);
	else
		return (CMD);
}

void	add_node(t_token **current, char *token)
{
	t_token	*new_node;
	t_token	*last_node;

	new_node = malloc(sizeof(t_token));
	new_node->content = ft_strdup(token);
	new_node->type = token_type(token);
	new_node->c_len = ft_strlen(token);
	if (*current == NULL)
	{
		new_node->id = 0;
		new_node->prev = NULL;
		new_node->next = NULL;
		*current = new_node;
	}
	else
	{
		last_node = *current;
		while (last_node->next)
			last_node = last_node->next;
		new_node->id = last_node->id + 1;
		new_node->prev = last_node;
		new_node->next = NULL;
		last_node->next = new_node;
	}
}

void	tokenize(t_main *pgr, char *cmd)
{
	char	**tokens;
	int		i;

	i = 0;
	tokens = tokenize_aux(cmd);
	pgr->token_amount = get_token_amount(cmd);
	pgr->tokens = NULL;
	while (i < pgr->token_amount)
		add_node(&pgr->tokens, tokens[i++]);
	free_double_array(tokens);
}

// int main(int argc, char const *argv[])
// {
//     t_main  *pgr;
//     char    *line_read;

//     while (1)
//     {
//         line_read = readline("minishell: ");
//         puts(line_read);
//         pgr = tokenize(line_read);
//         for (int i = 0; i < pgr->token_amount; i++)
//         {
//             printf("token:      %s\n", pgr->tokens->content);
//             printf("id:         %i\n", pgr->tokens->id);
//             printf("len token:  %i\n", pgr->tokens->c_len);
//             printf("type:       %i\n", pgr->tokens->type);
//             puts("\n* ------ * \n");
//             pgr->tokens = pgr->tokens->next;
//         }
//     }
//     return 0;
// }
