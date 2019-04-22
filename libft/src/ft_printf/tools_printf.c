/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   n_tools_printf.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dkotlyar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/24 12:57:15 by dkotlyar          #+#    #+#             */
/*   Updated: 2018/04/24 13:00:28 by dkotlyar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

char			*ft_strrev(char *str, int triger)
{
	int		i;
	int		len;
	char	*new;

	len = ft_strlen(str) - 1;
	MALLOC_CHECK_NULL(new = ft_strnew(len + 1));
	i = 0;
	while (len >= 0)
		new[i++] = str[len--];
	new[i] = '\0';
	if (triger)
		free(str);
	return (new);
}

static	int		find_size(intmax_t n)
{
	int size;
	int del;

	del = 10;
	size = 0;
	while (n / del > 9)
	{
		del *= 10;
		size += 2;
	}
	return (size);
}

char			*ft_itoa_s(intmax_t n)
{
	char	*res;
	int		i;
	int		is_neg;

	is_neg = 0;
	if (n < -9223372036854775807)
		return (ft_strdup("-9223372036854775808"));
	MALLOC_CHECK_NULL(res = ft_strnew(find_size(n) + 1));
	if (n < 0)
	{
		n *= -1;
		is_neg = 1;
	}
	i = 0;
	while (n > 9)
	{
		res[i++] = n % 10 + '0';
		n /= 10;
	}
	res[i] = n + '0';
	if (is_neg)
		res[++i] = '-';
	res[++i] = '\0';
	return (ft_strrev(res, 1));
}

char			*ft_itoa_u(uintmax_t n)
{
	char	*res;
	int		i;

	if (n > 18446744073709551614LU)
		return (ft_strdup("18446744073709551615"));
	MALLOC_CHECK_NULL(res = ft_strnew(find_size(n) + 1));
	i = 0;
	while (n > 9)
	{
		res[i++] = n % 10 + '0';
		n /= 10;
	}
	res[i] = n + '0';
	res[i + 1] = '\0';
	return (ft_strrev(res, 1));
}

char			*ft_itoa_base(uintmax_t num, int base)
{
	int		i;
	char	*str;
	char	*tab;

	tab = "0123456789abcdef";
	i = 0;
	if (num == 0)
		return (ft_strdup("0\0"));
	if (num > 18446744073709551614LU && base == 8)
		return (ft_strdup("1777777777777777777777"));
	if (base < 2 || base > 16 || !(str = ft_strnew(17)))
		return (NULL);
	while (num > 0)
	{
		str[i++] = tab[num % base];
		num /= base;
	}
	str[i] = '\0';
	return (ft_strrev(str, 1));
}
