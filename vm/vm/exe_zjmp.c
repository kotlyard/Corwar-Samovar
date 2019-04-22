/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exe_zjmp.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vzomber <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/24 21:05:22 by vzomber           #+#    #+#             */
/*   Updated: 2018/11/24 21:05:30 by vzomber          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

void	zjmp_logs(t_tool *tool, t_carriage *carg, int ok)
{
	if (ft_strchr(tool->output, 'd'))
	{
		ft_printf("P %4d | zjmp %d ", carg->carg_numb, carg->args.av1);
		if (ok)
			ft_printf("OK\n");
		else
		{
			ft_printf("FAILED\n");
			ft_strchr(tool->output, 'f') ?
				print_pc_move(tool, carg, DIR - 2 + 1) : 0;
		}
	}
}

void	exe_zjmp(t_carriage *carg, t_tool *tool, int cycles)
{
	int	num;

	if (check_cycles_wait(carg, cycles))
		return ;
	num = (short)get_value(tool, carg->curr_place + 1, DIR - 2);
	if (carg->carry == 1)
	{
		carg->args.av1 = (num % IDX_MOD);
		zjmp_logs(tool, carg, 1);
		carg->curr_place += (num % IDX_MOD);
	}
	else if (carg->carry == 0)
	{
		carg->args.av1 = num;
		zjmp_logs(tool, carg, 0);
		carg->curr_place += (DIR - 2 + 1);
	}
	check_place(tool, carg);
}
