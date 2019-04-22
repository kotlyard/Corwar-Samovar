/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dkotlyar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/07 16:14:15 by dkotlyar          #+#    #+#             */
/*   Updated: 2017/11/21 18:28:45 by dkotlyar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int		ft_memcmp(const void *s1, const void *s2, size_t n)
{
	unsigned char	*str1;
	unsigned char	*str2;

	if (!n)
		return (0);
	str1 = (unsigned char*)s1;
	str2 = (unsigned char*)s2;
	if (str1 == str2)
		return (0);
	while (*str1 == *str2 && --n > 0)
	{
		str1++;
		str2++;
	}
	return (*str1 - *str2);
}
