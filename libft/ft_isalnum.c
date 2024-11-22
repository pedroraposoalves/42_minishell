/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isalnum.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pemirand <pemirand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/03 17:18:15 by pemirand          #+#    #+#             */
/*   Updated: 2024/10/29 16:35:35 by pemirand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft.h"

int	ft_isalnum(int c)
{
	int	is_alpha;
	int	is_num;

	is_alpha = (c >= 'A' && c <= 'Z') || (c >= 'a' && c <= 'z');
	is_num = (c >= '0' && c <= '9');
	return (is_alpha || is_num);
}
