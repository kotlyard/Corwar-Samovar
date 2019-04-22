/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strslpit.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dkotlyar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/14 18:13:29 by dkotlyar          #+#    #+#             */
/*   Updated: 2017/11/22 19:15:02 by dkotlyar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static	size_t	ft_count_words(char const *s, char c)
{
	size_t	count;
	size_t	i;

	if (!*s)
		return (0);
	count = 0;
	i = 0;
	while (s[i])
	{
		while (s[i] == c && s[i])
			i++;
		if (s[i] != c && s[i])
			count++;
		while (s[i] != c && s[i])
			i++;
	}
	return (count);
}

static	size_t	ft_count_chars(char const *s, char c)
{
	size_t		i;

	i = 0;
	while (s[i] != '\0' && s[i] != c)
		i++;
	return (i);
}

char			**ft_strsplit(char const *s, char c)
{
	size_t		i;
	size_t		j;
	char		**res;
	size_t		k;
	size_t		wlen;

	if (!s || !(res = (char**)malloc(sizeof(char*) *
		(ft_count_words(s, c) + 1))))
		return (NULL);
	i = 0;
	k = 0;
	while (k < ft_count_words(s, c))
	{
		while (s[i] == c && s[i])
			i++;
		if (!(res[k] = (char*)malloc(sizeof(char) *
			(wlen = ft_count_chars(&s[i], c)) + 1)))
			return (NULL);
		j = 0;
		while (j < wlen)
			res[k][j++] = s[i++];
		res[k++][j] = '\0';
	}
	res[k] = NULL;
	return (res);
}
