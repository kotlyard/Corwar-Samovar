/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   useful.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vzomber <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/15 13:44:11 by vzomber           #+#    #+#             */
/*   Updated: 2018/12/15 13:44:13 by vzomber          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

void	kill_all(t_tool *tool)
{
	t_carriage	*tmp;

	while (tool->carriages)
	{
		ft_strchr(tool->output, 'e') ? show_death(tool->carriages, tool) : 0;
		tmp = tool->carriages;
		tool->carg_qty--;
		tool->carriages = tool->carriages->next;
		free(tmp);
	}
}

int		check_correct_reg(int num1, int num2, int num3)
{
	if (num1 <= 0 || num1 > 16)
		return (1);
	if (num2 <= 0 || num2 > 16)
		return (1);
	if (num3 <= 0 || num3 > 16)
		return (1);
	return (0);
}

void	check_place(t_tool *tool, t_carriage *carg)
{
	carg->curr_place = MEM(carg->curr_place);
	carg->cmd = tool->map[carg->curr_place];
	carg->cycles_wait = 0;
}

void	end_of_the_game(t_tool *tool)
{
	if (!tool->visual && tool->dump && tool->cycles >= tool->dump)
		dump_map(tool);
	if (tool->visual && !tool->dump)
		stop_visual(tool);
	if (!tool->visual && !tool->dump)
		ft_printf("Contestant %d, \"%s\", has won !\n",
				ABS(tool->pl_arr[tool->last].numb),
				tool->pl_arr[tool->last].name);
}

void	end_game(t_tool *tool)
{
	wattron(tool->side_win, COLOR_PAIR(4));
	mvwprintw(tool->side_win, 1, 2, "** END OF THE GAME **");
	wattroff(tool->side_win, COLOR_PAIR(4));
	wattron(tool->side_win, COLOR_PAIR(1));
	mvwprintw(tool->side_win, 32, 2, "Winner ->[%d] %s ",
			tool->pl_arr[tool->last % 4].numb,
			tool->pl_arr[tool->last % 4].name);
	wattroff(tool->side_win, COLOR_PAIR(1));
	wrefresh(tool->side_win);
}
