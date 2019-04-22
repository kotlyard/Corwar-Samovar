/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dkotlyar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/21 17:50:39 by dkotlyar          #+#    #+#             */
/*   Updated: 2018/03/22 03:36:17 by dkotlyar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup(const char *str)
{
	size_t	len;
	char	*dp;

	len = ft_strlen(str) + 1;
	if (!(dp = ft_strnew(ft_strlen(str))))
		return (NULL);
	ft_memcpy(dp, str, len);
	return (dp);
}
