/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   matrix_handle.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pemirand <pemirand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/22 13:38:02 by pemirand          #+#    #+#             */
/*   Updated: 2024/11/22 17:27:29 by pemirand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

char	**matrix_dup(char **m)
{
	int		m_len;
	char	**res;

	m_len = 0;
	res = NULL;
	if (!m)
		return (res);
	while (m[m_len])
		m_len++;
	res = (char **)malloc(sizeof(char *) * (m_len + 1));
	res[m_len--] = NULL;
	while (m_len >= 0)
	{
		res[m_len] = ft_strdup(m[m_len]);
		m_len--;
	}
	return (res);
}

int	matrix_len(char **m)
{
	int	len;

	len = 0;
	if (!m)
		return (len);
	while (m[len])
		len++;
	return (len);
}

void	free_matrix(char **m)
{
	int		m_len;

	m_len = 0;
	if (m)
	{
		while (m[m_len])
		{
			free(m[m_len]);
			m_len++;
		}
		free(m);
	}
}
