/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exe_lld.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vzomber <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/27 12:51:36 by vzomber           #+#    #+#             */
/*   Updated: 2018/11/27 12:51:44 by vzomber          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

int		lld_logs(t_tool *tool, t_carriage *carg)
{
	if (ft_strchr(tool->output, 'd'))
	{
		ft_printf("P %4d | lld ", carg->carg_numb);
		return (1);
	}
	return (0);
}

/*
** 31 line was like this -> (unsigned int)get_value(tool,
**								carg->curr_place + 2, IND);
*/

int		first_param_lld(t_tool *tool, t_carriage *carg, int num)
{
	num = (unsigned int)get_ind_value(tool, carg->curr_place, 0);
	num = (short)get_value(tool, carg->curr_place + num, 2);
	return (num);
}

void	second_part_lld(t_tool *tool, t_carriage *carg, int len, int reg)
{
	(carg->reg[reg] == 0) ? (carg->carry = 1) :
		(carg->carry = 0);
	ft_strchr(tool->output, 'f') ? print_pc_move(tool, carg, len) : 0;
	carg->curr_place += len;
	check_place(tool, carg);
}

void	exe_lld(t_carriage *carg, t_tool *tool, int cycles)
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
	carg->args.all_len = lab_length(num, av1, av2, 0);
	if (num == 0 || !av1 || av2 != REG)
		return (skip(tool, carg, carg->args.all_len));
	if (av1 == IND)
		num = first_param_lld(tool, carg, num);
	else
		num = (short)get_value(tool, carg->curr_place + 2, DIR - 2);
	tmp = (unsigned char)get_value(tool, carg->curr_place + 2 + av1, REG);
	if (check_correct_reg(tmp, 1, 1))
		return (skip(tool, carg, carg->args.all_len));
	carg->reg[tmp] = (unsigned int)num;
	(av1 == DIR) ? (av1 = 2) : 0;
	lld_logs(tool, carg) ? ft_printf("%d r%d\n", num, tmp) : 0;
	second_part_lld(tool, carg, 2 + av1 + av2, tmp);
}
