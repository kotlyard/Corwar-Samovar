/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   algorithm.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vzomber <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/13 16:21:03 by vzomber           #+#    #+#             */
/*   Updated: 2018/11/13 16:21:05 by vzomber          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

/*
** Executes each carriage's command once and move it if there is no command.
*/

void	exec_cmd_2(t_carriage *carg, t_tool *tool)
{
	if (carg->cmd == 7)
		exe_or(carg, tool, 6);
	else if (carg->cmd == 8)
		exe_xor(carg, tool, 6);
	else if (carg->cmd == 9)
		exe_zjmp(carg, tool, 20);
	else if (carg->cmd == 10)
		exe_ldi(carg, tool, 25);
	else if (carg->cmd == 11)
		exe_sti(carg, tool, 25);
	else if (carg->cmd == 12)
		exe_fork(carg, tool, 800);
	else if (carg->cmd == 13)
		exe_lld(carg, tool, 10);
	else if (carg->cmd == 14)
		exe_lldi(carg, tool, 50);
	else if (carg->cmd == 15)
		exe_lfork(carg, tool, 1000);
	else if (carg->cmd == 16)
		exe_aff(carg, tool, 2);
}

void	exec_cmd(t_carriage *carg, t_tool *tool)
{
	if (carg->cmd <= 0 || carg->cmd > 16)
	{
		carg->curr_place = MEM(carg->curr_place++);
		carg->cmd = tool->map[carg->curr_place];
	}
	else if (carg->cmd == 1)
		exe_live(carg, tool, 10);
	else if (carg->cmd == 2)
		exe_ld(carg, tool, 5);
	else if (carg->cmd == 3)
		exe_st(carg, tool, 5);
	else if (carg->cmd == 4)
		exe_add(carg, tool, 10);
	else if (carg->cmd == 5)
		exe_sub(carg, tool, 10);
	else if (carg->cmd == 6)
		exe_and(carg, tool, 6);
	else
		exec_cmd_2(carg, tool);
}

/*
** While is out of the function(algo)
** because of The Norm.
** Just counts alive carriages and execute theirs commands above.
*/

void	cargs_exe(t_tool *tool)
{
	t_carriage *carg;

	carg = tool->carriages;
	while (carg)
	{
		carg->tmp = 0;
		exec_cmd(carg, tool);
		carg = carg->next;
	}
}

/*
** Main cycle of the game, with all the conditions.
** if necessary, watch vm.h.
*/

void	algo_cycle(t_tool *tool, int *count, int *cycles)
{
	ft_strchr(tool->output, 'c') ?
		ft_printf("It is now cycle %d\n", tool->cycles) : 0;
	cargs_exe(tool);
	if (*cycles == tool->cycles_to_die)
	{
		*cycles = 0;
		check_alive_cargs(tool);
		if (tool->lives >= NBR_LIVE || *count == MAX_CHECKS)
		{
			*count = 1;
			tool->cycles_to_die -= CYCLE_DELTA;
			ft_strchr(tool->output, 'c') ?
				ft_printf("Cycle to die is now %d\n", tool->cycles_to_die) : 0;
		}
		else
			(*count)++;
		tool->lives = 0;
	}
}

void	algo(t_tool *tool)
{
	int				cycles;
	int				count;

	count = 1;
	cycles = 1;
	tool->cycles = 1;
	tool->visual ? nodelay(stdscr, 1) : 0;
	while (tool->cycles_to_die > 0 && tool->carg_qty > 0)
	{
		algo_cycle(tool, &count, &cycles);
		cycles++;
		tool->cycles++;
		getch() == 32 ? tool->e_status = PAUSE : 0;
		tool->visual ? visual(tool) : 0;
		if (tool->dump && tool->cycles == tool->dump + 1)
			break ;
	}
	if (!tool->dump)
	{
		algo_cycle(tool, &count, &cycles);
		if (tool->carg_qty > 0)
			kill_all(tool);
	}
}
