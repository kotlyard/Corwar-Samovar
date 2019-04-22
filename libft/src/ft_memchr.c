/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dkotlyar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/07 15:57:24 by dkotlyar          #+#    #+#             */
/*   Updated: 2017/11/21 17:41:03 by dkotlyar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memchr(const void *s, int c, size_t n)
{
	unsigned long	i;
	unsigned char	*new;
	unsigned char	sym;

	new = (unsigned char*)s;
	sym = (unsigned char)c;
	i = 0;
	while (i < n)
	{
		if (new[i] == sym)
			return (&new[i]);
		i++;
	}
	return (NULL);
}
