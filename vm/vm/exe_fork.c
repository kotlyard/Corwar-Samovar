/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exe_fork.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vzomber <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/26 17:09:55 by vzomber           #+#    #+#             */
/*   Updated: 2018/11/26 17:10:03 by vzomber          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

void	fork_logs(t_tool *tool, t_carriage *carg)
{
	if (ft_strchr(tool->output, 'd'))
		ft_printf("P %4d | fork %d (%d)\n", carg->carg_numb, carg->args.av1,
			carg->args.av2);
}

void	exe_fork(t_carriage *carg, t_tool *tool, int cycles)
{
	int			num;
	int			pos;

	if (check_cycles_wait(carg, cycles))
		return ;
	carg->cycles_wait = 0;
	num = (short)get_value(tool, carg->curr_place + 1, DIR - 2);
	pos = MEM(carg->curr_place + (num % IDX_MOD));
	make_carriage(carg->pl_id, tool, pos);
	tool->carriages->carry = carg->carry;
	tool->carriages->pl_id = carg->pl_id;
	ft_memcpy(&tool->carriages->reg, &carg->reg, sizeof(carg->reg));
	tool->carg_qty++;
	carg->args.av1 = num;
	carg->args.av2 = pos;
	fork_logs(tool, carg);
	ft_strchr(tool->output, 'f') ? print_pc_move(tool, carg, 3) : 0;
	carg->curr_place += 3;
	check_place(tool, carg);
}
