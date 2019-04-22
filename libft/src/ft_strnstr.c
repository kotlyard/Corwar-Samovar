/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dkotlyar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/03 14:20:29 by dkotlyar          #+#    #+#             */
/*   Updated: 2017/11/21 17:24:15 by dkotlyar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *str1, const char *str2, size_t n)
{
	size_t			i;
	int				j;

	i = 0;
	if (str2[0] == '\0')
		return (char*)(str1);
	while (str1[i] && i < n)
	{
		j = 0;
		while (str2[j] == str1[i + j] && i + j < n)
		{
			if (str2[j + 1] == '\0')
				return (char*)(&str1[i]);
			j++;
		}
		i++;
	}
	return (NULL);
}
