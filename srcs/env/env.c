/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pemirand <pemirand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/29 16:03:46 by pemirand          #+#    #+#             */
/*   Updated: 2025/01/12 14:12:51 by pemirand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

char	*get_env_value(char *variable, t_main *pgr)
{
	int		v_len;
	char	*tmp;
	char	**env;

	env = pgr->cur_envp;
	v_len = ft_strlen(variable);
	if (!env)
		return (NULL);
	while (*env)
	{
		tmp = ft_substr(*env, 0, v_len + 1);
		if (ft_strncmp(tmp, variable, v_len) == 0 && tmp[v_len] == '=')
			return (free(tmp), *env);
		free(tmp);
		env++;
	}
	return (NULL);
}

int	set_env_value(char *variable, t_main *pgr, char *new_v)
{
	int		v_len;
	char	*tmp;
	char	**env;

	env = pgr->cur_envp;
	v_len = ft_strlen(variable);
	if (!env)
		return (EXIT_FAILURE);
	while (*env)
	{
		tmp = ft_substr(*env, 0, v_len + 1);
		if (ft_strncmp(tmp, variable, v_len) == 0 && tmp[v_len] == '=')
		{
			free(*env);
			*env = ft_strjoin(tmp, new_v);
			return (free(tmp), EXIT_SUCCESS);
		}
		free(tmp);
		env++;
	}
	return (EXIT_FAILURE);
}

int	del_env_value(char *variable, t_main *pgr)
{
	int		v_len;
	char	*tmp;
	char	**env;

	env = pgr->cur_envp;
	v_len = ft_strlen(variable);
	if (!env)
		return (EXIT_FAILURE);
	while (*env)
	{
		tmp = ft_substr(*env, 0, v_len + 1);
		if (ft_strncmp(tmp, variable, v_len) == 0 && tmp[v_len] == '=')
		{
			free(*env);
			while (*(++env))
				*(env - 1) = *env;
			*(env - 1) = NULL;
		}
		free(tmp);
		if (!env[0] || !env[1])
			break ;
		env++;
	}
	return (EXIT_SUCCESS);
}

int	append_env_value(char *variable, t_main *pgr)
{
	int		env_len;
	char	**res;

	if (!pgr->cur_envp)
		return (EXIT_FAILURE);
	env_len = 0;
	while (pgr->cur_envp[env_len])
		env_len++;
	res = (char **)malloc(sizeof(char *) * (env_len + 2));
	res[env_len + 1] = NULL;
	res[env_len] = ft_strjoin(variable, "=");
	while (env_len-- > 0)
		res[env_len] = pgr->cur_envp[env_len];
	free (pgr->cur_envp);
	pgr->cur_envp = res;
	return (EXIT_SUCCESS);
}
