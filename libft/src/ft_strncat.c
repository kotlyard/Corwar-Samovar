/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dkotlyar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/21 17:57:15 by dkotlyar          #+#    #+#             */
/*   Updated: 2017/11/21 18:02:52 by dkotlyar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strncat(char *dest, const char *src, size_t n)
{
	size_t	i;
	int		end;

	end = ft_strlen(dest);
	i = 0;
	while (i < n && src[i])
	{
		dest[end + i] = src[i];
		i++;
	}
	dest[end + i] = '\0';
	return (dest);
}
