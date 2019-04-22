/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dkotlyar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/07 15:06:14 by dkotlyar          #+#    #+#             */
/*   Updated: 2017/11/29 14:34:51 by dkotlyar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memcpy(void *dst, const void *src, size_t n)
{
	unsigned long		i;
	unsigned char		*res;
	const unsigned char *fg;

	fg = (const unsigned char*)src;
	res = (unsigned char*)dst;
	i = 0;
	while (i < n)
	{
		res[n - i - 1] = fg[n - i - 1];
		i++;
	}
	return (res);
}
