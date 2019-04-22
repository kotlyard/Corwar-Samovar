/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   float.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dkotlyar <dkotlyar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/24 11:53:29 by dkotlyar          #+#    #+#             */
/*   Updated: 2018/05/06 20:14:27 by dkotlyar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int				save_width(char *str)
{
	int i;

	i = 0;
	while (str[i])
	{
		if (ft_isdigit(str[i]) && str[i] != '0' && str[i - 1] != '.')
			return (ft_atoi(&str[i]));
		i++;
	}
	return (0);
}

char			save_size(char *str)
{
	if (ft_strchr(str, 'h') && !ft_strstr(str, "hh"))
		return ('h');
	if (ft_strstr(str, "hh"))
		return ('H');
	if (ft_strchr(str, 'l') && !ft_strstr(str, "ll"))
		return ('l');
	if (ft_strstr(str, "ll"))
		return ('L');
	if (ft_strchr(str, 'j'))
		return ('j');
	if (ft_strchr(str, 'z'))
		return ('z');
	return (' ');
}

static	int		acc_rate(long long acc)
{
	int res;

	res = 1;
	while (0 < acc--)
		res *= 10;
	return (res);
}

static char		*ft_fillchr(char c, int len)
{
	char	*res;
	int		i;

	MALLOC_CHECK_NULL(res = ft_strnew(len));
	i = 0;
	while (len-- > 0)
		res[i++] = c;
	return (res);
}

char			*h_float(t_arg_info info, va_list lst)
{
	long long	before;
	long long	after;
	char		*res;
	char		*tmp;
	double		num;

	num = va_arg(lst, double);
	tmp = ft_itoa_s(num);
	before = num;
	res = ft_itoa(before);
	if (info.acc == 0)
		return (res);
	res = ft_strjoin_deluxe(res, ".", 1);
	if (num - before != 0)
	{
		after = (num - before) * (info.acc < 6 && info.acc != -1 ?
		acc_rate(info.acc) : 1000000) + (num >= 0 ? 0.5 : -0.5);
		tmp = ft_itoa(after < 0 ? after * -1 : after);
		res = ft_strjoin_deluxe(res, tmp, 1);
	}
	else if (info.acc != 0)
		res = ft_strjoin_deluxe(res,
		ft_fillchr('0', (info.acc == -1 ? 6 : info.acc)), 2);
	ft_strdel(&tmp);
	return (res);
}
