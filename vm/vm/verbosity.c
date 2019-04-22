/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   verbosity.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vzomber <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/29 15:09:26 by vzomber           #+#    #+#             */
/*   Updated: 2018/11/29 15:09:37 by vzomber          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

int		no_code_length(int av1, int av2, int av3)
{
	int	res;

	res = 1;
	res += av1;
	res += av2;
	res += av3;
	return (res);
}

int		lab_length(int num, int av1, int av2, int av3)
{
	int	res;

	if (num == 0)
		return (2);
	res = 2;
	av1 == DIR ? av1 = 2 : 0;
	av2 == DIR ? av2 = 2 : 0;
	av3 == DIR ? av3 = 2 : 0;
	res += av1;
	res += av2;
	res += av3;
	return (res);
}

int		length(int num, int av1, int av2, int av3)
{
	int	res;

	if (num == 0)
		return (2);
	res = 2;
	res += av1;
	res += av2;
	res += av3;
	return (res);
}

void	skip(t_tool *tool, t_carriage *carg, int len)
{
	ft_strchr(tool->output, 'f') ? print_pc_move(tool, carg, len) : 0;
	carg->curr_place += len;
	carg->cycles_wait = 0;
	carg->cmd = tool->map[carg->curr_place];
}

void	print_pc_move(t_tool *tool, t_carriage *carg, int len)
{
	int	i;

	if (tool->visual)
		return ;
	ft_printf("ADV %d (0x%.4x -> 0x%.4x) ", len, carg->curr_place,
		carg->curr_place + len);
	i = -1;
	while (++i < len)
		ft_printf("%.2x ", tool->map[MEM(carg->curr_place + i)]);
	ft_putchar('\n');
}
