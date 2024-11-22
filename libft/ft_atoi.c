/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pemirand <pemirand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/10 09:36:26 by pemirand          #+#    #+#             */
/*   Updated: 2024/10/29 16:33:06 by pemirand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft.h"

static size_t	ft_num_len(char *n)
{
	size_t	i;
	size_t	res;
	int		bool_left_zero;

	i = 0;
	res = 0;
	bool_left_zero = 1;
	while (n[i] && n[i] >= '0' && n[i++] <= '9')
	{
		if (bool_left_zero)
			if (n[i] >= '1')
				bool_left_zero = 0;
		if (!bool_left_zero)
			res++;
	}
	return (res);
}

static int	rm_spaces_signal(char **str)
{
	int	i;
	int	signal;

	signal = 1;
	i = 0;
	while (**str == ' ' || (**str >= 9 && **str <= 13))
		(*str)++;
	if (*str[i] == '-')
	{
		signal = -signal;
		(*str)++;
	}
	else if (*str[i] == '+')
		(*str)++;
	return (signal);
}

int	ft_atoi(const char *str)
{
	int			signal;
	size_t		len;
	long int	res;
	char		*tmp;

	tmp = (char *)str;
	res = 0;
	signal = rm_spaces_signal(&tmp);
	len = ft_num_len(tmp);
	if (len > 19)
	{
		if (signal == 1)
			return (-1);
		else
			return (0);
	}
	while (*tmp >= '0' && *tmp <= '9' && *tmp != '\0')
	{
		res = res * 10 + *tmp - '0';
		tmp++;
	}
	return ((int) res * signal);
}
