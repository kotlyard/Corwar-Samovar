/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   write_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vzomber <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/25 13:17:00 by vzomber           #+#    #+#             */
/*   Updated: 2018/12/25 13:17:02 by vzomber          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

void	write_map_sti(t_tool *tool, t_carriage *carg, int nums, int av1)
{
	write_map(tool, carg->curr_place + (nums % IDX_MOD),
		carg->reg[av1], sizeof(carg->reg[av1]));
	write_map_color(tool, carg->curr_place + (nums % IDX_MOD),
		sizeof(carg->reg[av1]), carg);
}

void	write_map_color(t_tool *tool, int pos, int len, t_carriage *carg)
{
	int	i;

	if (tool->visual)
	{
		i = -1;
		while (++i < len)
		{
			tool->colors[MEM(pos + i)] = (unsigned char)(carg->pl_id + 1);
			tool->bold[MEM(pos + i)] = 70;
		}
	}
}

void	write_map(t_tool *tool, int pos, int src, size_t len)
{
	int				i;
	unsigned char	a[5];

	a[0] = (unsigned char)(src >> 24);
	a[1] = (unsigned char)(src >> 16);
	a[2] = (unsigned char)(src >> 8);
	a[3] = (unsigned char)src;
	a[4] = '\0';
	i = -1;
	while (++i < (int)len)
		tool->map[MEM(pos + i)] = a[i];
}
