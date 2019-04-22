/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dkotlyar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/17 14:15:16 by dkotlyar          #+#    #+#             */
/*   Updated: 2017/11/23 20:54:48 by dkotlyar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static	int		is_space(char c)
{
	return (c == ' ' || c == '\n' || c == '\t' || c == '\v' ||
			c == '\f' || c == '\r');
}

int				ft_atoi(const char *str)
{
	size_t					i;
	unsigned long int		res;
	int						sign;

	i = 0;
	sign = 1;
	res = 0;
	while (is_space(str[i]) && str[i])
		i++;
	if (str[i] == '-' || str[i] == '+')
	{
		if (str[i] == '-')
			sign = -1;
		i++;
	}
	while ((ft_isdigit(str[i]) && str[i]))
	{
		res = res * 10 + (str[i] - '0') % 10;
		if (res >= 9223372036854775807 && sign == 1)
			return (-1);
		else if (res > 9223372036854775807 && sign == -1)
			return (0);
		i++;
	}
	return ((int)(res * sign));
}
