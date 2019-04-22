/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dkotlyar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/14 18:55:05 by dkotlyar          #+#    #+#             */
/*   Updated: 2018/07/06 19:44:14 by dkotlyar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static	char		*reverse_str(char *str)
{
	char	*rev;
	int		i;
	int		len;

	len = 0;
	while (str[len])
		len++;
	if (!(rev = (char*)malloc(sizeof(char) * len + 1)))
		return (NULL);
	i = 0;
	while (str[i])
	{
		rev[i] = str[len - 1];
		len--;
		i++;
	}
	rev[i] = '\0';
	return (rev);
}

static	size_t		find_size(intmax_t n)
{
	size_t size;
	size_t del;

	del = 10;
	size = 0;
	while (n / del > 9)
	{
		del *= 10;
		size += 2;
	}
	return (size);
}

char				*ft_itoa(intmax_t n)
{
	char			*res;
	int				i;
	int				is_neg;
	intmax_t		num;

	is_neg = 0;
	num = n;
	if (num < 0)
	{
		num *= -1;
		is_neg = 1;
	}
	if (!(res = (char*)malloc(find_size(num) + 1 + is_neg)))
		return (NULL);
	i = 0;
	while (num > 9)
	{
		res[i++] = num % 10 + '0';
		num /= 10;
	}
	res[i] = num + '0';
	if (is_neg)
		res[++i] = '-';
	res[i + 1] = '\0';
	return (reverse_str(res));
}
