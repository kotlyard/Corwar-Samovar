/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exe_live.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vzomber <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/13 16:50:03 by vzomber           #+#    #+#             */
/*   Updated: 2018/11/13 16:50:20 by vzomber          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

int		check_cycles_wait(t_carriage *carg, int cycles)
{
	if (carg->cycles_wait < cycles - 1)
	{
		carg->cycles_wait++;
		return (1);
	}
	return (0);
}

void	set_player_alive(t_tool *tool, int num)
{
	int	i;

	i = -1;
	while (++i < tool->pl_qty)
	{
		if (tool->pl_arr[i].numb == num)
		{
			tool->last = tool->pl_arr[i].id;
			tool->pl_arr[i].alive++;
			if (ft_strchr(tool->output, 'b'))
				ft_printf("Player %d (%s) is said to be alive\n",
					ABS(num), tool->pl_arr[i].name);
		}
	}
}

int		get_ind_value(t_tool *tool, int place, int param)
{
	int	num;

	num = (short)get_value(tool, place + 2 + param, IND);
	num = (unsigned int)get_value(tool, place + num, 4);
	return (num);
}

/*
** 'live' command.
** set carg and player from args alive
*/

void	exe_live(t_carriage *carg, t_tool *tool, int cycles)
{
	int	num;

	if (check_cycles_wait(carg, cycles))
		return ;
	tool->lives++;
	carg->alive = 1;
	carg->born = tool->cycles;
	num = (unsigned int)get_value(tool, carg->curr_place + 1, DIR);
	if (ft_strchr(tool->output, 'd'))
		ft_printf("P %4d | live %d\n", carg->carg_numb, num);
	set_player_alive(tool, num);
	ft_strchr(tool->output, 'f') ? print_pc_move(tool, carg, 5) : 0;
	carg->curr_place += (DIR + 1);
	check_place(tool, carg);
}
