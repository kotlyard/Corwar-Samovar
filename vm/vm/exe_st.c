/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exe_st.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vzomber <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/19 16:47:09 by vzomber           #+#    #+#             */
/*   Updated: 2018/11/19 16:47:11 by vzomber          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

int		st_logs(t_tool *tool, t_carriage *carg)
{
	if (ft_strchr(tool->output, 'd'))
	{
		ft_printf("P %4d | st ", carg->carg_numb);
		return (1);
	}
	return (0);
}

void	second_part_st(t_tool *tool, t_carriage *carg, int reg)
{
	int	num;

	num = (unsigned char)get_value(tool, carg->curr_place + 3, REG);
	if (check_correct_reg(1, 1, num))
		return (skip(tool, carg, carg->args.all_len));
	carg->reg[num] = carg->reg[reg];
	st_logs(tool, carg) ? ft_printf("r%d %d\n", reg, num) : 0;
	ft_strchr(tool->output, 'f') ? print_pc_move(tool, carg, 4) : 0;
	carg->curr_place += 4;
}

void	first_part_st(t_tool *tool, t_carriage *carg, int reg)
{
	int	num;

	num = (short)get_value(tool, carg->curr_place + 2 + REG, IND);
	write_map(tool, carg->curr_place + (num % IDX_MOD), carg->reg[reg],
		sizeof(carg->reg[reg]));
	write_map_color(tool, carg->curr_place + (num % IDX_MOD),
		sizeof(carg->reg[reg]), carg);
	st_logs(tool, carg) ? ft_printf("r%d %d\n", reg, num) : 0;
	ft_strchr(tool->output, 'f') ? print_pc_move(tool,
		carg, 2 + REG + IND) : 0;
	carg->curr_place += (2 + REG + IND);
}

void	exe_st(t_carriage *carg, t_tool *tool, int cycles)
{
	int	num;
	int	av1;
	int	av2;
	int	reg;

	if (check_cycles_wait(carg, cycles))
		return ;
	num = (unsigned char)get_value(tool, carg->curr_place + 1, 1);
	av1 = argv1(num);
	av2 = argv2(num);
	carg->args.all_len = length(num, av1, av2, 0);
	if (num == 0 || av1 != REG || !av2)
		return (skip(tool, carg, length(num, av1, av2, 0)));
	reg = (unsigned char)get_value(tool, carg->curr_place + 2, REG);
	if (check_correct_reg(1, 1, reg))
		return (skip(tool, carg, carg->args.all_len));
	if (av2 == IND)
		first_part_st(tool, carg, reg);
	else if (av2 == REG)
		second_part_st(tool, carg, reg);
	check_place(tool, carg);
}
