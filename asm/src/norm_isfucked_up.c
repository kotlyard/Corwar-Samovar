/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   norm_isfucked_up.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dkotlyar <dkotlyar@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/27 14:52:13 by dkotlyar          #+#    #+#             */
/*   Updated: 2018/12/27 14:52:29 by dkotlyar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

char	*mk_magic(char *str, char *const op_name)
{
	char *before;
	char *after;
	char *tmp;

	before = ft_strsub(str, 0, ft_strlen(op_name));
	tmp = ft_strjoin(before, " ");
	ft_strdel(&before);
	after = ft_strjoin(tmp, &str[ft_strlen(op_name)]);
	ft_strdel(&tmp);
	return (after);
}

int		ch_fuck(char *str)
{
	int	i;

	i = -1;
	while (++i < 16)
	{
		if (ft_strnequ(str, g_tab[i].op_name, ft_strlen(g_tab[i].op_name)))
		{
			if (i != 2 && i != 3 && i != 4 && i != 10 && i != 15)
				if (str[ft_strlen(g_tab[i].op_name)] == '%')
					return (i);
		}
	}
	return (-1);
}
