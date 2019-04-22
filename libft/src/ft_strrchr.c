/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dkotlyar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/03 15:33:45 by dkotlyar          #+#    #+#             */
/*   Updated: 2017/11/21 17:24:30 by dkotlyar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	char	*res;
	int		i;
	char	sym;

	sym = (char)c;
	res = NULL;
	i = 0;
	while (s[i])
	{
		if (s[i] == sym)
			res = (char*)&s[i];
		if (s[i + 1] == '\0' && sym == '\0')
			return (char*)(&s[i + 1]);
		s++;
	}
	return (res);
}
