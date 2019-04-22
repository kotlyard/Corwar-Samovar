/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dkotlyar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/21 14:40:59 by dkotlyar          #+#    #+#             */
/*   Updated: 2017/11/21 17:22:24 by dkotlyar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t dstsize)
{
	size_t d;
	size_t s;

	d = 0;
	while (dst[d])
		d++;
	s = 0;
	while (src[s] && d + s < dstsize - 1 && dstsize)
	{
		dst[d + s] = src[s];
		s++;
	}
	dst[d + s] = '\0';
	return (((dstsize > d) ? d : dstsize) + ft_strlen(src));
}
