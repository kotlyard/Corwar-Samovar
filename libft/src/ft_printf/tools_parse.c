/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools_parse.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dkotlyar <dkotlyar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/30 01:35:49 by dkotlyar          #+#    #+#             */
/*   Updated: 2018/04/24 13:45:01 by dkotlyar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

size_t			get_arg_num(char *s)
{
	size_t	res;
	int		i;

	i = 0;
	res = 0;
	while (s[i])
	{
		if (s[i] == '%')
			res++;
		i++;
	}
	return (res);
}

int				save_acc(char *str)
{
	int i;

	i = 0;
	while (str[i])
		if (str[i++] == '.')
			return (ft_atoi(&str[i]));
	return (-1);
}

int				find_prezero(char *str)
{
	int i;

	i = 0;
	while (str[i])
	{
		if (str[0] == '0' || (str[i] == '0' && str[i - 1] != '.' &&
			str[i] && !ft_isdigit(str[i - 1])))
			return (1);
		i++;
	}
	return (0);
}

char			save_spec(char *str)
{
	if (ft_strchr(str, 's') || ft_strchr(str, 'S'))
		return (ft_strchr(str, 's') ? 's' : 'S');
	else if (ft_strchr(str, 'c') || ft_strchr(str, 'C'))
		return (ft_strchr(str, 'c') ? 'c' : 'C');
	else if (ft_strchr(str, 'd') || ft_strchr(str, 'D') || ft_strchr(str, 'i'))
		return (ft_strchr(str, 'D') ? 'D' : 'd');
	else if (ft_strchr(str, 'x') || ft_strchr(str, 'X'))
		return (ft_strchr(str, 'x') ? 'x' : 'X');
	else if (ft_strchr(str, 'p'))
		return ('p');
	else if (ft_strchr(str, 'o') || ft_strchr(str, 'O'))
		return (ft_strchr(str, 'o') ? 'o' : 'O');
	else if (ft_strchr(str, 'u') || ft_strchr(str, 'U'))
		return (ft_strchr(str, 'u') ? 'u' : 'U');
	else if (ft_strchr(str, 'f') || ft_strchr(str, 'F'))
		return (ft_strchr(str, 'f') ? 'f' : 'F');
	else if (ft_strchr(str, '%'))
		return ('%');
	return (' ');
}

void			save_flag(char *str, t_arg_info *format)
{
	if (ft_strchr(str, '-'))
		format->is_left_just = 1;
	else
		format->is_left_just = 0;
	if (ft_strchr(str, '#'))
		format->is_octotorp = 1;
	else
		format->is_octotorp = 0;
	if (format->is_left_just == 0 && find_prezero(str))
		format->is_prezero = 1;
	else
		format->is_prezero = 0;
	if (ft_strchr(str, '+'))
		format->plus_or_space = 1;
	else if (ft_strchr(str, ' '))
		format->plus_or_space = 2;
	else
		format->plus_or_space = 0;
}
