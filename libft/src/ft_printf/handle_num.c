/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_num.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dkotlyar <dkotlyar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/24 12:10:51 by dkotlyar          #+#    #+#             */
/*   Updated: 2018/05/06 20:15:32 by dkotlyar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static	char		*to_upper(char *str)
{
	int i;

	if (!str)
		return (NULL);
	i = 0;
	if (ft_strlen(str) < 1)
		return (str);
	while (str[i])
	{
		str[i] -= str[i] >= 'a' && str[i] <= 'z' ? 32 : 0;
		i++;
	}
	return (str);
}

static	intmax_t	handle_num_s(t_arg_info info, va_list lst)
{
	intmax_t	num;

	num = 0;
	if (info.size == 'h' && info.spec != 'D')
		num = (short)va_arg(lst, int);
	else if (info.size == 'H' && info.spec != 'D')
		num = (char)va_arg(lst, int);
	else if (info.size == 'l' || info.spec == 'D')
		num = va_arg(lst, long);
	else if (info.size == 'L' && info.spec != 'D')
		num = va_arg(lst, long long);
	else if (info.size == 'j')
		num = va_arg(lst, intmax_t);
	else if (info.size == 'z')
		num = va_arg(lst, long);
	else if (info.size == ' ')
		num = va_arg(lst, int);
	return (num);
}

static	uintmax_t	handle_num_u(t_arg_info info, va_list lst)
{
	uintmax_t	num;

	num = 0;
	if (info.size == 'h' && info.spec != 'U')
		num = (unsigned short)va_arg(lst, unsigned int);
	else if (info.size == 'H' && info.spec != 'U' && info.spec != 'O')
		num = (unsigned char)va_arg(lst, unsigned int);
	else if (info.size == 'l' || info.spec == 'U' || info.spec == 'O')
		num = va_arg(lst, unsigned long);
	else if (info.size == 'L')
		num = va_arg(lst, unsigned long long);
	else if (info.size == 'j')
		num = va_arg(lst, uintmax_t);
	else if (info.size == 'z')
		num = va_arg(lst, size_t);
	else if (info.size == ' ')
		num = va_arg(lst, unsigned int);
	return (num);
}

char				*h_plus_or_space(char *out, t_arg_info info)
{
	if ((info.spec == 'd' || info.spec == 'f' || info.spec == 'F') &&
		info.plus_or_space == 1)
		return (out[0] == '-' ? out : ft_strjoin_deluxe("+", out, 2));
	else if ((info.spec == 'd' || info.spec == 'f' || info.spec == 'F') &&
			info.plus_or_space == 2)
		return (out[0] == '-' ? out : ft_strjoin_deluxe(" ", out, 2));
	return (out);
}

char				*h_num(t_arg_info info, va_list lst)
{
	intmax_t	s_res;
	uintmax_t	u_res;
	char		*out;

	out = NULL;
	s_res = 0;
	if (info.spec == 'd' || info.spec == 'D')
	{
		s_res = handle_num_s(info, lst);
		out = ft_itoa_s(s_res);
	}
	else if (info.spec == 'u' || info.spec == 'U')
	{
		u_res = handle_num_u(info, lst);
		out = ft_itoa_u(u_res);
	}
	else if (info.spec == 'x' || info.spec == 'X' || info.spec == 'o' ||
			info.spec == 'O')
	{
		s_res = handle_num_u(info, lst);
		out = info.spec == 'o' || info.spec == 'O' ? ft_itoa_base(s_res, 8) :
			ft_itoa_base(s_res, 16);
		out = info.spec == 'X' ? to_upper(out) : out;
	}
	return (s_res == 0 && info.acc == 0 ? ft_strdup("\0") : out);
}
