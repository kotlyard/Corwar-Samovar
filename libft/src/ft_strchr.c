/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dkotlyar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/03 15:18:26 by dkotlyar          #+#    #+#             */
/*   Updated: 2018/12/27 18:22:06 by dkotlyar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strchr(const char *s, int c)
{
	char	sym;
	int		i;

	i = 0;
	if (!s)
		return (NULL);
	sym = (char)c;
	while (s[i] != sym)
		if (s[i++] == '\0')
			return (NULL);
	return (char*)(&s[i]);
}
