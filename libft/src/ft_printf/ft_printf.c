/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dkotlyar <dkotlyar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/24 12:01:11 by dkotlyar          #+#    #+#             */
/*   Updated: 2018/04/24 13:46:01 by dkotlyar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static	t_arg_info		save_format(char *str, t_arg_info format)
{
	format.len = (int)ft_strlen(str);
	format.spec = save_spec(str);
	save_flag(str, &format);
	format.width = save_width(str);
	format.acc = save_acc(str);
	format.size = save_size(str);
	if (format.spec == ' ' && !is_valid(str[format.len - 1]))
		format.spec = str[format.len - 1];
	return (format);
}

static	t_arg_info		*parse_format(char *f, t_arg_info *format)
{
	int		i;
	int		j;
	int		k;
	char	save[ft_strlen(f) + 1];

	i = 0;
	k = 0;
	while (f[i])
	{
		if (f[i++] == '%' && f[i])
		{
			j = 0;
			ft_strclr(save);
			while (j != -1 && f[i] && is_valid(f[i - 1]))
			{
				save[j++] = f[i++];
				save[j] = '\0';
				j = is_spec(f[i - 1]) == 1 ? -1 : j;
			}
			format[k] = save_format(save, format[k]);
			k++;
		}
	}
	return (format);
}

long long				inner_2(t_arg_info info, va_list lst)
{
	unsigned int c;

	if (info.spec == 'p')
		return (h_width(info, h_octotorp(info, h_acc(info,
				ft_itoa_base(va_arg(lst, long long), 16)))));
	else if (info.spec == 'C' || (info.spec == 'c' && info.size == 'l'))
	{
		c = va_arg(lst, unsigned int);
		if (c > 32)
			return (h_width(info, handle_wchar(c)));
		return (handle_char(c, info));
	}
	else if (info.spec == 'c' && info.size != 'l')
		return (handle_char(va_arg(lst, unsigned int), info));
	else if (info.spec == '%')
		return (h_width(info, "%"));
	else
		return (h_width(info, get_s_from_c(info)));
}

long long				inner(t_arg_info info, va_list lst)
{
	if (info.spec == 'd' || info.spec == 'u' || info.spec == 'U' ||
		info.spec == 'D')
		return (h_width(info, h_plus_or_space(h_acc(info,
								h_num(info, lst)), info)));
	else if (info.spec == 'o' || info.spec == 'O' || info.spec == 'x' ||
			info.spec == 'X')
		return (h_width(info, h_octotorp(info, h_acc(info, h_num(info, lst)))));
	else if (info.spec == 's' && info.size != 'l')
		return (h_width(info, h_acc(info, va_arg(lst, char*))));
	else if (info.spec == 'S' || (info.spec == 's' && info.size == 'l'))
		return (h_width(info, h_wstring(va_arg(lst, unsigned int*), info)));
	else if (info.spec == 'f' || info.spec == 'F')
		return (h_width(info, h_plus_or_space(h_float(info, lst), info)));
	else
		return (inner_2(info, lst));
}

int						ft_printf(char *s, ...)
{
	va_list		lst;
	intmax_t	ret;
	t_arg_info	format[get_arg_num(s) + 1];
	int			k;
	int			i;

	ret = 0;
	i = 0;
	k = 0;
	va_start(lst, s);
	parse_format(s, format);
	while (s[i] && i < (int)ft_strlen(s))
	{
		if (s[i] == '%')
		{
			ret += inner(format[k], lst);
			i += format[k++].len + (i >= (int)ft_strlen(s) ? 0 : 1);
		}
		if (s[i] != '%' && s[i] && format[k - 1].spec != '\0')
			ret += write(1, &s[i++], 1);
	}
	va_end(lst);
	return (ret);
}
