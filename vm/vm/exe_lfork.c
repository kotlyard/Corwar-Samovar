/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exe_lfork.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vzomber <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/27 13:46:52 by vzomber           #+#    #+#             */
/*   Updated: 2018/11/27 13:47:01 by vzomber          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

void	lfork_logs(t_tool *tool, t_carriage *carg)
{
	if (ft_strchr(tool->output, 'd'))
		ft_printf("P %4d | lfork %d (%d)\n", carg->carg_numb, carg->args.av1,
			carg->args.av2);
}

void	exe_lfork(t_carriage *carg, t_tool *tool, int cycles)
{
	int			num;
	int			pos;

	if (check_cycles_wait(carg, cycles))
		return ;
	carg->cycles_wait = 0;
	num = (short)get_value(tool, carg->curr_place + 1, DIR - 2);
	pos = MEM(carg->curr_place + num);
	make_carriage(carg->pl_id, tool, pos);
	tool->carriages->carry = carg->carry;
	tool->carriages->pl_id = carg->pl_id;
	ft_memcpy(&tool->carriages->reg, &carg->reg, sizeof(carg->reg));
	tool->carg_qty++;
	carg->args.av1 = num;
	carg->args.av2 = pos;
	lfork_logs(tool, carg);
	ft_strchr(tool->output, 'f') ? print_pc_move(tool, carg, 3) : 0;
	carg->curr_place += 3;
	check_place(tool, carg);
}
