/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exe_aff.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vzomber <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/27 13:51:23 by vzomber           #+#    #+#             */
/*   Updated: 2018/11/27 13:51:35 by vzomber          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

int		aff_logs(t_tool *tool, t_carriage *carg)
{
	if (ft_strchr(tool->output, 'd'))
	{
		ft_printf("P %4d | aff ", carg->carg_numb);
		return (1);
	}
	return (0);
}

void	exe_aff(t_carriage *carg, t_tool *tool, int cycles)
{
	int	num;
	int	av1;

	if (check_cycles_wait(carg, cycles))
		return ;
	num = (unsigned char)get_value(tool, carg->curr_place + 1, 1);
	av1 = argv1(num);
	if (num == 0 || av1 != REG)
		return (skip(tool, carg, no_code_length(av1, 0, 0)));
	num = (unsigned char)get_value(tool, carg->curr_place + 2, REG);
	if (check_correct_reg(num, 1, 1))
		return (skip(tool, carg, 2));
	ft_printf("%c\n", carg->reg[num] % 256);
	aff_logs(tool, carg) ? ft_printf("%d\n", num) : 0;
	ft_strchr(tool->output, 'f') ? print_pc_move(tool, carg, 1) : 0;
	carg->curr_place += REG + 1;
	check_place(tool, carg);
}
