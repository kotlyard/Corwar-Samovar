/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dkotlyar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/17 14:23:17 by dkotlyar          #+#    #+#             */
/*   Updated: 2018/12/12 19:41:05 by dkotlyar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static	int		is_space(char c)
{
	return (c == ' ' || c == '\n' || c == '\t');
}

char			*ft_strtrim(char const *s)
{
	char			*res;
	size_t			j;

	if (!s)
		return (NULL);
	while (is_space(*s))
		s++;
	j = ft_strlen(s);
	while (is_space(s[j - 1]) && j > 0)
		j--;
	if (!(res = (char*)malloc(sizeof(char) * (j + 1))))
		return (NULL);
	ft_strncpy(res, s, j);
	res[j] = '\0';
	return (res);
}
