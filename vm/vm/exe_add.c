/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exe_add.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vzomber <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/20 14:44:17 by vzomber           #+#    #+#             */
/*   Updated: 2018/11/20 14:44:32 by vzomber          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

int		add_logs(t_tool *tool, t_carriage *carg)
{
	if (ft_strchr(tool->output, 'd'))
	{
		ft_printf("P %4d | add ", carg->carg_numb);
		return (1);
	}
	return (0);
}

void	exe_add(t_carriage *carg, t_tool *tool, int cycles)
{
	int	num;
	int	av1;
	int	av2;
	int	av3;

	if (check_cycles_wait(carg, cycles))
		return ;
	num = (unsigned char)get_value(tool, carg->curr_place + 1, 1);
	av1 = argv1(num);
	av2 = argv2(num);
	av3 = argv3(num);
	if (num == 0 || av1 != REG || av2 != REG || av3 != REG)
		return (skip(tool, carg, length(num, av1, av2, av3)));
	av1 = (unsigned char)get_value(tool, carg->curr_place + 2, REG);
	av2 = (unsigned char)get_value(tool, carg->curr_place + 3, REG);
	av3 = (unsigned char)get_value(tool, carg->curr_place + 4, REG);
	if (check_correct_reg(av1, av2, av3))
		return (skip(tool, carg, 5));
	carg->reg[av3] = carg->reg[av1] + carg->reg[av2];
	(carg->reg[av3] == 0) ? (carg->carry = 1) :
		(carg->carry = 0);
	add_logs(tool, carg) ? ft_printf("r%d r%d r%d\n", av1, av2, av3) : 0;
	ft_strchr(tool->output, 'f') ? print_pc_move(tool, carg, 5) : 0;
	carg->curr_place += (2 + 3);
	check_place(tool, carg);
}
