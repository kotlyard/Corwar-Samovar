/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exe_sti.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vzomber <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/26 13:50:28 by vzomber           #+#    #+#             */
/*   Updated: 2018/11/26 13:50:36 by vzomber          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

void	sti_logs(t_tool *tool, t_carriage *carg)
{
	if (ft_strchr(tool->output, 'd'))
		ft_printf("P %4d | sti r%d %d %d\n", carg->carg_numb,
			carg->args.av1, carg->args.av2, carg->args.av3);
}

int		second_param_sti(t_carriage *carg, t_tool *tool, int av1, int av2)
{
	int num;

	num = 0;
	carg->tmp = 0;
	if (av2 == DIR)
		num = (short)get_value(tool, carg->curr_place + 2 + av1, DIR - 2);
	else if (av2 == REG)
	{
		num = (unsigned char)get_value(tool, carg->curr_place + 2 + av1, REG);
		if (num > 0 && num <= 16)
			num = carg->reg[num];
		else
			carg->tmp = 1;
	}
	else if (av2 == IND)
	{
		num = (short)get_value(tool, carg->curr_place + 2 + av1, IND);
		num = (unsigned int)get_value(tool, carg->curr_place +
			(num % IDX_MOD), 4);
	}
	carg->args.av2 = num;
	return (num);
}

int		third_param_sti(t_carriage *carg, t_tool *tool, int args, int av3)
{
	int num;

	num = 0;
	carg->tmp = 0;
	if (av3 == REG)
	{
		num = (unsigned char)get_value(tool, carg->curr_place + 2 + args, REG);
		if (num > 0 && num <= 16)
			num = carg->reg[num];
		else
			carg->tmp = 1;
	}
	else if (av3 == DIR)
		num = (short)get_value(tool, carg->curr_place + 2 + args, DIR - 2);
	carg->args.av3 = num;
	return (num);
}

void	second_part_sti(t_tool *tool, t_carriage *carg, int len)
{
	sti_logs(tool, carg);
	ft_strchr(tool->output, 'f') ? print_pc_move(tool, carg, len) : 0;
	carg->curr_place += len;
	check_place(tool, carg);
}

void	exe_sti(t_carriage *carg, t_tool *tool, int cycles)
{
	int num2;
	int av1;
	int av2;
	int av3;
	int num3;

	if (check_cycles_wait(carg, cycles))
		return ;
	num2 = (unsigned char)get_value(tool, carg->curr_place + 1, 1);
	av1 = argv1(num2);
	av2 = argv2(num2);
	av3 = argv3(num2);
	if (num2 == 0 || av1 != REG || !av2 || !av3)
		return (skip(tool, carg, lab_length(num2, av1, av2, av3)));
	av1 = (unsigned char)get_value(tool, carg->curr_place + 2, REG);
	carg->args.av1 = av1;
	num2 = second_param_sti(carg, tool, REG, av2);
	(av2 == DIR) ? (av2 = 2) : 0;
	num3 = third_param_sti(carg, tool, REG + av2, av3);
	(av3 == DIR) ? (av3 = 2) : 0;
	if (carg->tmp || check_correct_reg(av1, 1, 1))
		return (skip(tool, carg, carg->args.all_len));
	write_map_sti(tool, carg, num2 + num3, av1);
	second_part_sti(tool, carg, 2 + REG + av2 + av3);
}
