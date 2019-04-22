/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exe_ldi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vzomber <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/24 21:19:52 by vzomber           #+#    #+#             */
/*   Updated: 2018/11/24 21:20:09 by vzomber          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

void	ldi_logs(t_tool *tool, t_carriage *carg)
{
	if (ft_strchr(tool->output, 'd'))
		ft_printf("P %4d | ldi %d %d r%d\n", carg->carg_numb,
			carg->args.av1, carg->args.av2, carg->args.av3);
}

int		second_param_ldi(t_carriage *carg, t_tool *tool, int av1, int av2)
{
	int	num;

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
	carg->args.av2 = num;
	return (num);
}

int		first_param_ldi(t_carriage *carg, t_tool *tool, int av1)
{
	int	num;

	num = 0;
	carg->tmp = 0;
	if (av1 == IND)
	{
		num = (short)get_value(tool, carg->curr_place + 2, IND);
		num = (unsigned int)get_value(tool, carg->curr_place +
			(num % IDX_MOD), 4);
	}
	else if (av1 == DIR)
		num = (short)get_value(tool, carg->curr_place + 2, DIR - 2);
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

void	second_part_ldi(t_tool *tool, t_carriage *carg, int len)
{
	ldi_logs(tool, carg);
	ft_strchr(tool->output, 'f') ? print_pc_move(tool, carg, len) : 0;
	carg->curr_place += len;
	check_place(tool, carg);
}

void	exe_ldi(t_carriage *carg, t_tool *tool, int cycles)
{
	int	num1;
	int	av1;
	int	av2;
	int	av3;
	int	num2;

	VCHECK(check_cycles_wait(carg, cycles));
	num1 = (unsigned char)get_value(tool, carg->curr_place + 1, 1);
	av1 = argv1(num1);
	av2 = argv2(num1);
	av3 = argv3(num1);
	carg->args.all_len = lab_length(num1, av1, av2, av3);
	if (num1 == 0 || !av1 || !av2 || av3 != REG)
		return (skip(tool, carg, carg->args.all_len));
	num1 = first_param_ldi(carg, tool, av1);
	(av1 == DIR) ? (av1 -= 2) : 0;
	num2 = second_param_ldi(carg, tool, av1, av2);
	(av2 == DIR) ? (av2 -= 2) : 0;
	av3 = (unsigned char)get_value(tool, carg->curr_place + 2 + av1 + av2, REG);
	carg->args.av3 = av3;
	if (carg->tmp || check_correct_reg(1, 1, av3))
		return (skip(tool, carg, carg->args.all_len));
	carg->reg[av3] = (unsigned int)get_value(tool,
		carg->curr_place + ((num1 + num2) % IDX_MOD), 4);
	second_part_ldi(tool, carg, 2 + av1 + av2 + REG);
}
