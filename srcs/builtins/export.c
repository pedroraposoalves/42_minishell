/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pemirand <pemirand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/21 09:25:10 by pemirand          #+#    #+#             */
/*   Updated: 2025/01/21 14:14:54 by pemirand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int		order_print_stack(char **stack);
char	*export_check_var(char *var);
int		ft_export_update_env(t_main *pgr, char *var_name, char *var);

int	ft_export(t_main *pgr, char **argv)
{
	int		i;
	char	*var_name;
	int		argc;

	argc = matrix_len(argv);
	i = 1;
	if (argc == 1 && argv)
		order_print_stack(pgr->cur_envp);
	else if (argc > 1 && argv)
	{
		while (i++ < argc)
		{
			var_name = export_check_var(argv[i - 1]);
			if (var_name != NULL)
				ft_export_update_env(pgr, var_name, argv[i - 1]);
		}
	}
	return (EXIT_SUCCESS);
}

char	*export_check_var(char *var)
{
	int		equal_pos;
	int		var_len;
	char	*var_name;

	var_len = ft_strlen(var);
	if (var_len <= 0 && var[0]!='\0')
		return (NULL);
	equal_pos = ft_str_char(var, '=');
	var_name = ft_substr(var, 0, equal_pos);
	if ((isalpha(var[0]) || var[0] == '_') && \
		(ft_specialcharpos_export(var_name) == -1 || (var[equal_pos - 1] == '+' \
		&& ft_specialcharpos_export(var_name) == equal_pos - 1)))
		return (var_name);
	else
	{
		g_exit = 1;
		print_error(SHELL_NAME, "export", var, "not a valid identifier");
	}
	return (free(var_name), NULL);
}

int	order_print_stack(char **stack)
{
	char	**dup_stack;
	int		s_len;

	if (!stack)
		return (EXIT_FAILURE);
	s_len = 0;
	while (stack[s_len])
		s_len++;
	dup_stack = matrix_dup(stack);
	dup_stack = ft_sort_char_tab(dup_stack, s_len);
	if (!dup_stack)
		return (EXIT_FAILURE);
	s_len = 0;
	while (dup_stack[s_len])
	{
		ft_putstr_fd("declare -x ", STDOUT_FILENO);
		ft_putendl_fd(dup_stack[s_len++], STDOUT_FILENO);
	}
	free_matrix(dup_stack);
	return (EXIT_SUCCESS);
}

void	ft_export_update_env_append(t_main *pgr, char *var_name, char *var)
{
	char	*tmp1;
	char	*tmp2;

	var_name[ft_strlen(var_name) - 1] = '\0';
	tmp1 = get_env_value(var_name, pgr);
	if (tmp1 == NULL)
	{
		append_env_value(var_name, pgr);
		set_env_value(var_name, pgr, &var[ft_str_char(var, '=') + 1]);
	}
	else
	{
		tmp1 = ft_substr(tmp1, ft_strlen(var_name) \
				+ 1, ft_strlen(tmp1) - ft_strlen(var_name) - 1);
		tmp2 = ft_strjoin(tmp1, &var[ft_str_char(var, '=') + 1]);
		set_env_value(var_name, pgr, tmp2);
		free(tmp1);
		free(tmp2);
	}
}

int	ft_export_update_env(t_main *pgr, char *var_name, char *var)
{
	int		append_flag;

	if (var_name == NULL)
		return (EXIT_FAILURE);
	append_flag = 0;
	if (var[ft_str_char(var, '=') - 1] == '+')
		append_flag = 1;
	if (append_flag == 0)
	{
		if (ft_strlen(var_name) == ft_strlen(var))
			append_env_value(var_name, pgr);
		else if (set_env_value(var_name, pgr, \
			&var[ft_str_char(var, '=') + 1]) == EXIT_FAILURE)
		{
			append_env_value(var_name, pgr);
			set_env_value(var_name, pgr, &var[ft_str_char(var, '=') + 1]);
		}
	}
	else
		ft_export_update_env_append(pgr, var_name, var);
	free(var_name);
	return (EXIT_SUCCESS);
}
