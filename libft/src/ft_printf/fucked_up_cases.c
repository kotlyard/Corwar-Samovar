/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fucked_up_cases.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dkotlyar <dkotlyar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/24 11:57:01 by dkotlyar          #+#    #+#             */
/*   Updated: 2018/04/24 13:45:20 by dkotlyar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int					is_spec(char i)
{
	if (i == 'd' || i == 'D' || i == 'i' || i == 'X' ||
		i == 's' || i == 'S' || i == 'c' || i == 'C' ||
		i == 'F' || i == 'f' || i == 'p' || i == 'x' ||
		i == 'o' || i == 'O' || i == 'u' || i == 'U' ||
		i == '%')
		return (1);
	return (0);
}

int					is_valid(char c)
{
	if (!is_spec(c) && !ft_isdigit(c) && c != '#' && c != ' ' &&
		c != '-' && c != '+' && c != 'h' && c != 'l' &&
		c != 'j' && c != 'z' && c != '.')
		return (0);
	return (1);
}

char				*get_s_from_c(t_arg_info info)
{
	char	tmp[2];
	char	*str;

	tmp[0] = info.spec;
	tmp[1] = '\0';
	str = tmp;
	return (str);
}

char				*ft_strjoin_deluxe(char *s1, char *s2, int triger)
{
	char	*res;

	res = NULL;
	if (s1 != NULL && s2 != NULL)
	{
		res = ft_strnew(ft_strlen(s1) + ft_strlen(s2));
		if (res != NULL)
		{
			ft_strcpy(res, s1);
			ft_strcat(res, s2);
		}
	}
	if (triger == 1)
		ft_memdel((void**)&s1);
	else if (triger == 2 && !ft_strequ(s2, "\0"))
		ft_memdel((void**)&s2);
	else if (triger == 3)
	{
		ft_memdel((void**)&s1);
		ft_memdel((void**)&s2);
	}
	return (res);
}

char				*ft_push_start(char c, char *s, int acc)
{
	char	*new;
	int		i;
	int		len;

	if (!s)
		return (NULL);
	len = acc - ft_strlen(s);
	MALLOC_CHECK_NULL(new = ft_strnew(ft_strlen(s) + acc + 1));
	i = 0;
	while (len-- > 0)
		new[i++] = c;
	ft_strcpy(&new[i], s);
	free(s);
	return (new);
}
