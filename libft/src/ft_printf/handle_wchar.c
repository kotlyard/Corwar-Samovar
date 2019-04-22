/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_wchar.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dkotlyar <dkotlyar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/24 12:26:16 by dkotlyar          #+#    #+#             */
/*   Updated: 2018/04/24 13:44:55 by dkotlyar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static	int		what_is_len(int x)
{
	if (x < (1 << 7))
		return (1);
	else if (x < (1 << 11))
		return (2);
	else if (x < (1 << 16))
		return (3);
	else
		return (4);
}

int				handle_char(char c, t_arg_info info)
{
	int		ret;
	char	space;

	ret = 0;
	space = info.is_prezero == 1 && info.acc < 1 &&
		info.is_left_just == 0 ? '0' : ' ';
	if (info.is_left_just == 0)
	{
		while (1 < info.width--)
			ret += write(1, &space, 1);
		ret += write(1, &c, 1);
	}
	else
	{
		ret += write(1, &c, 1);
		while (1 < info.width--)
			ret += write(1, &space, 1);
	}
	return (ret);
}

static	char	*paste_together(char **arr)
{
	int		i;
	char	*str;

	i = 0;
	str = NULL;
	while (arr[i])
	{
		if (i == 0)
		{
			MALLOC_CHECK_NULL(str = ft_strdup(arr[i]));
		}
		else
		{
			MALLOC_CHECK_NULL(str = ft_strjoin_deluxe(str, arr[i], 1));
		}
		ft_strdel(&arr[i++]);
	}
	ft_memdel((void**)(&arr));
	return (str);
}

char			*h_wstring(unsigned int *tab, t_arg_info info)
{
	char	**arr;
	int		i;
	int		len;

	i = 0;
	if (!tab)
		return (ft_strdup("(null)\0"));
	while (tab[i])
		i++;
	MALLOC_CHECK_NULL(arr = (char**)malloc(sizeof(char*) * (i + 1)));
	len = i;
	i = 0;
	while (i < len)
	{
		if (what_is_len(tab[i]) > info.acc && info.acc != -1)
			break ;
		else
		{
			info.acc -= info.acc == -1 ? 0 : what_is_len(tab[i]);
			arr[i] = handle_wchar(tab[i]);
		}
		i++;
	}
	arr[i] = NULL;
	return (i == 0 ? ft_strdup("\0") : paste_together(arr));
}

char			*handle_wchar(unsigned int x)
{
	char	*arr;

	MALLOC_CHECK_NULL(arr = ft_strnew(what_is_len(x)));
	if (what_is_len(x) == 4)
	{
		arr[3] = (x & 63) | 128;
		arr[2] = ((x >> 6) & 63) | 128;
		arr[1] = ((x >> 12) & 63) | 128;
		arr[0] = ((x >> 18) & 7) | 240;
	}
	else if (what_is_len(x) == 3)
	{
		arr[2] = (x & 63) | 128;
		arr[1] = ((x >> 6) & 63) | 128;
		arr[0] = ((x >> 12) & 15) | 224;
	}
	else if (what_is_len(x) == 2)
	{
		arr[1] = (x & 63) | 128;
		arr[0] = ((x >> 6) & 31) | 192;
	}
	else
		arr[0] = x;
	return (arr);
}
