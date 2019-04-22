/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exe_ld.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vzomber <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/16 14:00:27 by vzomber           #+#    #+#             */
/*   Updated: 2018/11/16 14:00:39 by vzomber          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

int		ld_logs(t_tool *tool, t_carriage *carg)
{
	if (ft_strchr(tool->output, 'd'))
	{
		ft_printf("P %4d | ld ", carg->carg_numb);
		return (1);
	}
	return (0);
}

void	second_part_ld(t_tool *tool, t_carriage *carg, int reg, int len)
{
	(carg->reg[reg] == 0) ? (carg->carry = 1)
		: (carg->carry = 0);
	ft_strchr(tool->output, 'f') ? print_pc_move(tool, carg, len) : 0;
	carg->curr_place += len;
	check_place(tool, carg);
}

int		first_param_ld(t_tool *tool, t_carriage *carg, int num)
{
	num = (short)get_value(tool, carg->curr_place + 2, IND);
	num = (unsigned int)get_value(tool, carg->curr_place +
		(num % IDX_MOD), 4);
	return (num);
}

void	exe_ld(t_carriage *carg, t_tool *tool, int cycles)
{
	int num;
	int av1;
	int av2;
	int tmp;

	if (check_cycles_wait(carg, cycles))
		return ;
	num = (unsigned char)get_value(tool, carg->curr_place + 1, 1);
	av1 = argv1(num);
	av2 = argv2(num);
	carg->args.all_len = length(num, av1, av2, 0);
	if (num == 0 || !av1 || av2 != REG)
		return (skip(tool, carg, carg->args.all_len));
	if (av1 == IND)
		num = first_param_ld(tool, carg, num);
	else
		num = (unsigned int)get_value(tool, carg->curr_place + 2, DIR);
	tmp = (unsigned char)get_value(tool, carg->curr_place + 2 + av1, REG);
	if (check_correct_reg(tmp, 1, 1))
		return (skip(tool, carg, carg->args.all_len));
	carg->reg[tmp] = (unsigned int)num;
	ld_logs(tool, carg) ? ft_printf("%d r%d\n", num, tmp) : 0;
	second_part_ld(tool, carg, tmp, 2 + av1 + av2);
}
