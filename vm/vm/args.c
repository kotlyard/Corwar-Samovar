/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   args.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vzomber <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/23 13:13:55 by vzomber           #+#    #+#             */
/*   Updated: 2018/11/23 13:14:06 by vzomber          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

int		get_value(t_tool *tool, int place, int len)
{
	long int		i;
	unsigned char	a[5];
	int				res;

	a[0] = tool->map[MEM(place)];
	a[1] = tool->map[MEM(place + 1)];
	a[2] = tool->map[MEM(place + 2)];
	a[3] = tool->map[MEM(place + 3)];
	a[4] = '\0';
	i = -1;
	res = 0;
	while (++i < len)
		res = (res << 8) | a[i];
	return (res);
}

int		argv1(int num)
{
	num = num >> 6;
	if (num == DIR_CODE)
		return (DIR);
	else if (num == IND_CODE)
		return (IND);
	else if (num == REG_CODE)
		return (REG);
	return (0);
}

int		argv2(int num)
{
	num = (num >> 4) & 0x3;
	if (num == DIR_CODE)
		return (DIR);
	else if (num == IND_CODE)
		return (IND);
	else if (num == REG_CODE)
		return (REG);
	return (0);
}

int		argv3(int num)
{
	num = (num >> 2) & 0x3;
	if (num == DIR_CODE)
		return (DIR);
	else if (num == IND_CODE)
		return (IND);
	else if (num == REG_CODE)
		return (REG);
	return (0);
}
