/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   width_and_acc.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dkotlyar <dkotlyar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/24 12:34:13 by dkotlyar          #+#    #+#             */
/*   Updated: 2018/04/24 13:45:12 by dkotlyar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

char				*h_octotorp(t_arg_info info, char *str)
{
	if (info.spec == 'p' && info.acc != 0 && info.is_prezero == 0)
		return (ft_strjoin_deluxe("0x", str, 2));
	if (info.spec == 'p' && info.width != -1 && info.is_prezero == 1)
		return (ft_strjoin("0x", ft_push_start('0', str, info.width - 2)));
	if (info.acc == -1 && info.spec != 'o' && info.spec != 'p' &&
		(ft_strequ(str, "0") || ft_strequ(str, "")))
		return (str);
	else if (info.is_octotorp == 1 || info.spec == 'p')
	{
		if (info.spec == 'p' && info.acc == 0 && info.is_prezero == 0)
			return ("0x");
		else if (!ft_strequ(str, "") && !ft_strequ(str, "0") &&
				(info.spec == 'x' || info.spec == 'p'))
			return (ft_strjoin("0x", str));
		else if (info.spec == 'X')
			return (ft_strjoin_deluxe("0X", str, 2));
		else if (!ft_strequ(str, "0") && !ft_strequ(str, "") &&
				(info.spec == 'x' || info.spec == 'X'))
			return (str);
		else if (!ft_strequ(str, "0") && (info.spec == 'o' || info.spec == 'O'))
			return (ft_strjoin("0", str));
	}
	return (str);
}

long long			h_width_2(t_arg_info info, char **str, char c)
{
	int		len;
	int		ret;

	ret = 0;
	len = (int)ft_strlen(*str);
	if (info.is_left_just == 1)
	{
		ret += write(1, *str, len);
		while (len < info.width--)
			ret += write(1, &c, 1);
	}
	if (*str)
	{
		if (info.spec == 'd' || info.spec == 'D' || info.spec == 'U' ||
			info.spec == 'u' || info.spec == 'X' || info.spec == 'x')
			ft_strdel(str);
		if ((info.spec == 'p' && info.acc != 0))
			ft_strdel(str);
		if ((info.spec == 'C' && ft_strlen(*str) > 1) || info.spec == 'S')
			ft_strdel(str);
		if (info.spec == 'o' || info.spec == 'O')
			ft_strdel(str);
	}
	return (ret);
}

long long			h_width(t_arg_info info, char *str)
{
	int			len;
	char		c;
	long long	ret;

	ret = 0;
	c = info.is_prezero == 1 && (info.acc < 1 || !is_spec(info.spec)) &&
		info.is_left_just == 0 ? '0' : ' ';
	if (!str)
		return (1);
	len = ft_strlen(str);
	if (info.acc == -1 && info.width != -1 && info.is_octotorp == 1 &&
		info.is_prezero == 1 && (info.spec == 'x' || info.spec == 'X'))
		return (write(1, str, len));
	else if (info.is_left_just == 0)
	{
		while (len < info.width--)
			ret += write(1, &c, 1);
		ret += write(1, str, len);
	}
	return (ret + h_width_2(info, &str, c));
}

static char			*handle_bad_acc(t_arg_info *info, char *str)
{
	if (!str)
		str = info->acc != -1 ? "" : "(null)";
	if (info->acc == -1 && info->width != -1 && info->is_octotorp == 1 &&
		info->is_prezero == 1 && info->is_left_just == 0 &&
		(info->spec == 'x' || info->spec == 'X'))
		info->acc = info->width - 2;
	else if (info->acc == -1 && info->width != -1 && info->is_octotorp == 0 &&
			info->is_prezero == 1 && info->is_left_just == 0 &&
			(info->spec == 'd' || info->spec == 'D' ||
			info->spec == 'u' || info->spec == 'U'))
		info->acc = info->width - 1;
	else if ((info->spec == 'o' || info->spec == 'O') &&
			info->acc != -1 && info->is_octotorp == 1)
		info->acc--;
	return (str);
}

char				*h_acc(t_arg_info info, char *s)
{
	int	len;

	s = handle_bad_acc(&info, s);
	len = (int)ft_strlen(s);
	if (s[0] == '-' && (info.spec == 'd' || info.spec == 'D') &&
		info.acc > 0 && info.acc >= len)
	{
		return (ft_strjoin("-", ft_push_start('0', ft_strdup(&s[1]),
				info.acc)));
	}
	if (info.acc > len++ && info.acc != -1 && info.spec != 's')
		return (ft_push_start('0', s, info.acc));
	if ((info.spec == 's' || info.spec == 'S') &&
		info.acc > -1 && info.acc < len)
		return (ft_strsub(s, 0, (size_t)info.acc));
	return (s);
}
