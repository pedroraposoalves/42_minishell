/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malves-b <malves-b@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/17 16:35:55 by malves-b          #+#    #+#             */
/*   Updated: 2025/01/12 10:46:33 by malves-b         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	get_return_last_cmd(char **content, int ret_last_cmd, int j)
{
	char	new_content[9000];
	char	*aux;
	int		i;
	int		x;

	i = 0;
	while (content[0][i])
	{
		if (content[0][i] == '$' && content[0][i + 1] == '?')
		{
			i++;
			aux = ft_itoa(ret_last_cmd);
			x = 0;
			while (aux[x])
				new_content[j++] = aux[x++];
			free(aux);
		}
		else
			new_content[j++] = content[0][i];
		i++;
	}
	new_content[j] = '\0';
	free (*content);
	*content = ft_strdup(new_content);
}

/** @brief Change the content value for the envp variable */
void	change_content(char *vrbl, char **content, int *i, int word_len)
{
	char	new_content[9000];
	int		j;
	int		aux;

	j = -1;
	while (++j < (*i))
		new_content[j] = content[0][j];
	aux = 0;
	while (vrbl[aux])
		new_content[j++] = vrbl[aux++];
	while (content[0][*i + ++word_len])
		new_content[j++] = content[0][*i + word_len];
	new_content[j] = '\0';
	free(*content);
	*content = ft_strdup(new_content);
}

void	set_envp_value(char **cont, char **envp, int i, int wrd)
{
	int	index;

	while (cont[0][i])
	{
		if (cont[0][i] == '$' && cont[0][i + 1] != '"' && cont[0][i + 1] != 32)
		{
			wrd = 0;
			while (cont[0][i + wrd + 1] && !ft_isspace(cont[0][i + wrd + 1])
				&& cont[0][i + wrd + 1] != '"' && cont[0][i + wrd + 1] != '\'')
				wrd++;
			index = -1;
			while (envp[++index] && cont[0][i])
			{
				wrd = cmp_env(envp[index], cont[0] + (i + 1));
				if (wrd)
					change_content(envp[index] + (wrd + 1), &cont[0], &i, wrd);
				if (wrd)
					break ;
				if (!envp[index + 1])
					(*cont) = remove_badenvp(cont, i);
			}
		}
		else
			i++;
	}
}

int	search_exp(char *content)
{
	int	i;
	int	ret;

	i = 0;
	ret = 0;
	while (content[i])
	{
		if (content[i] == '$')
		{
			if (!content[i + 1] && !ret)
				return (0);
			if (content[i + 1] == '?')
				ret = 2;
			else if (content[i + 1] == 32)
				i++;
			else if (!ret && !ft_isspace(content[i]))
				ret = 1;
		}
		i++;
	}
	return (ret);
}

void	ft_expand(t_main *main)
{
	t_token	*start;

	start = main->tokens;
	while (main->tokens)
	{
		if (search_exp(main->tokens->content)
			&& main->tokens->type != S_QUOTES
			&& (!main->tokens->prev || !main->tokens->prev->prev
				|| (main->tokens->prev->prev->type != HERE_DOC
					&& main->tokens->prev->type != HERE_DOC)))
		{
			if (search_exp(main->tokens->content) == 2)
			{
				get_return_last_cmd(&main->tokens->content,
					main->exit_status[0], 0);
			}
			set_envp_value(&main->tokens->content, main->cur_envp, 0, 0);
			main->tokens->c_len = ft_strlen(main->tokens->content);
		}
		if (main->tokens->next == NULL)
			break ;
		main->tokens = main->tokens->next;
	}
	main->tokens = start;
}

// int main(int argc, char *argv[])
// {
//     return 0;
// }
