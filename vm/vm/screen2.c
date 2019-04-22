/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   screen2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vzomber <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/27 14:53:07 by vzomber           #+#    #+#             */
/*   Updated: 2018/11/27 14:53:16 by vzomber          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

WINDOW	*create_newwin(int height, int width, int starty, int startx)
{
	WINDOW *local_win;

	local_win = newwin(height, width, starty, startx);
	box(local_win, 0, 0);
	wrefresh(local_win);
	return (local_win);
}

int		players(WINDOW *side_win, int line, t_tool *tool)
{
	int i;

	i = -1;
	while (++i < tool->pl_qty)
	{
		wattron(side_win, COLOR_PAIR(tool->pl_arr[i].id + 1));
		mvwprintw(side_win, line++, 2, "Player %d : %s \n",
			tool->pl_arr[i].numb, tool->pl_arr[i].name);
		wattroff(side_win, COLOR_PAIR(tool->pl_arr[i].id + 1));
		mvwprintw(side_win, line++, 4, "Lives in current period :\t\t%d    ",
			tool->pl_arr[i].alive);
		line++;
	}
	return (line);
}

void	side_panel(WINDOW *side_win, t_tool *tool)
{
	int line;

	line = 7;
	if (tool->e_status == PAUSE)
	{
		wattron(side_win, COLOR_PAIR(1));
		mvwprintw(side_win, 1, 2, "** PAUSED  **");
		wattroff(side_win, COLOR_PAIR(1));
	}
	else
	{
		wattron(side_win, COLOR_PAIR(2));
		mvwprintw(side_win, 1, 2, "** RUNNING **");
		wattroff(side_win, COLOR_PAIR(2));
	}
	mvwprintw(side_win, 3, 2, "Cycle : %d ", tool->cycles);
	mvwprintw(side_win, 5, 2, "Processes : %d ", tool->carg_qty);
	line = players(side_win, line, tool);
	mvwprintw(side_win, line, 2, "CYCLE_TO_DIE : %d ", tool->cycles_to_die);
	mvwprintw(side_win, line + 2, 2, "CYCLE_DELTA : %d ", CYCLE_DELTA);
}

void	paint_carg(t_tool *tool)
{
	t_carriage	*carg;
	int			color;

	carg = tool->carriages;
	while (carg)
	{
		carg->curr_place = MEM(carg->curr_place);
		color = tool->colors[carg->curr_place] + 10;
		wattron(tool->main_win, COLOR_PAIR(color));
		mvwprintw(tool->main_win, carg->curr_place / 64 + 1,
			2 + (carg->curr_place % 64) * 3, "%.2x",
			tool->map[carg->curr_place]);
		wattroff(tool->main_win, COLOR_PAIR(color));
		carg = carg->next;
	}
	wrefresh(tool->main_win);
}

void	main_panel(WINDOW *main_win, t_tool *tool)
{
	int		i;
	int		j;
	int		line;
	int		col;

	line = 1;
	i = -1;
	while (++i < 64)
	{
		col = 2;
		j = -1;
		while (++j < 64)
		{
			if (tool->bold[i * 64 + j] && (tool->bold[i * 64 + j] -= 1))
				wattron(main_win, A_BOLD);
			wattron(main_win, COLOR_PAIR(tool->colors[i * 64 + j]));
			mvwprintw(main_win, line, col, "%.2x ", tool->map[i * 64 + j]);
			wattroff(main_win, COLOR_PAIR(tool->colors[i * 64 + j]));
			if (tool->bold[i * 64 + j])
				wattroff(main_win, A_BOLD);
			col += 3;
		}
		line++;
	}
	paint_carg(tool);
}
