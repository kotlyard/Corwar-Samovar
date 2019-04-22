/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exe_xor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vzomber <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/24 21:00:39 by vzomber           #+#    #+#             */
/*   Updated: 2018/11/24 21:00:48 by vzomber          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

void	xor_logs(t_tool *tool, t_carriage *carg)
{
	if (ft_strchr(tool->output, 'd'))
		ft_printf("P %4d | xor %d %d r%d\n", carg->carg_numb, carg->args.av1,
			carg->args.av2, carg->args.av3);
}

int		second_param_xor(t_carriage *carg, t_tool *tool, int av2, int av1)
{
	int	num2;

	num2 = 0;
	carg->tmp = 0;
	if (av2 == IND)
		num2 = (unsigned int)get_ind_value(tool, carg->curr_place + av1, av1);
	else if (av2 == DIR)
		num2 = (unsigned int)get_value(tool, carg->curr_place + 2 + av1, DIR);
	else if (av2 == REG)
	{
		num2 = (unsigned char)get_value(tool, carg->curr_place + 2 + av1, REG);
		if (num2 > 0 && num2 <= 16)
			num2 = carg->reg[num2];
		else
			carg->tmp = 1;
	}
	carg->args.av2 = num2;
	return (num2);
}

int		first_param_xor(t_carriage *carg, t_tool *tool, int av1)
{
	int num;

	num = 0;
	carg->tmp = 0;
	if (av1 == IND)
		num = (unsigned int)get_ind_value(tool, carg->curr_place, 0);
	else if (av1 == DIR)
		num = (unsigned int)get_value(tool, carg->curr_place + 2, DIR);
	else if (av1 == REG)
	{
		num = (unsigned char)get_value(tool, carg->curr_place + 2, REG);
		if (num > 0 && num <= 16)
			num = carg->reg[num];
		else
			carg->tmp = 1;
	}
	carg->args.av1 = num;
	return (num);
}

void	second_part_xor(t_tool *tool, t_carriage *carg, int len, int reg)
{
	(carg->reg[reg] == 0) ? (carg->carry = 1)
		: (carg->carry = 0);
	xor_logs(tool, carg);
	ft_strchr(tool->output, 'f') ? print_pc_move(tool, carg, len) : 0;
	carg->curr_place += len;
	check_place(tool, carg);
}

void	exe_xor(t_carriage *carg, t_tool *tool, int cycles)
{
	int	num1;
	int	av1;
	int	av2;
	int	av3;
	int	num2;

	if (check_cycles_wait(carg, cycles))
		return ;
	num1 = (unsigned char)get_value(tool, carg->curr_place + 1, 1);
	av1 = argv1(num1);
	av2 = argv2(num1);
	av3 = argv3(num1);
	carg->args.all_len = length(num1, av1, av2, av3);
	if (!num1 || !av1 || !av2 || av3 != REG)
		return (skip(tool, carg, length(num1, av1, av2, av3)));
	num1 = first_param_xor(carg, tool, av1);
	num2 = second_param_xor(carg, tool, av2, av1);
	av3 = (unsigned char)get_value(tool, carg->curr_place + 2 + av1 + av2, REG);
	carg->args.av3 = av3;
	if (carg->tmp || check_correct_reg(1, 1, av3))
		return (skip(tool, carg, carg->args.all_len));
	carg->reg[av3] = (unsigned int)(num1 ^ num2);
	second_part_xor(tool, carg, 2 + av1 + av2 + REG, av3);
}
