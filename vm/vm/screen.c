/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   screen.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vzomber <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/27 14:53:07 by vzomber           #+#    #+#             */
/*   Updated: 2018/11/27 14:53:16 by vzomber          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

void	create_field(t_tool *tool)
{
	tool->main_win = create_newwin(66, 195, 1, 3);
	tool->side_win = create_newwin(66, 56, 1, 200);
	nodelay(tool->main_win, 1);
	nodelay(tool->side_win, 1);
	draw(tool);
}

void	draw(t_tool *tool)
{
	curs_set(0);
	usleep(DELAY);
	side_panel(tool->side_win, tool);
	main_panel(tool->main_win, tool);
	box(tool->side_win, 0, 0);
	box(tool->main_win, 0, 0);
	wrefresh(tool->main_win);
	wrefresh(tool->side_win);
}

void	init_window(t_tool *tool)
{
	initscr();
	cbreak();
	noecho();
	keypad(stdscr, TRUE);
	create_field(tool);
	start_color();
	init_pair(1, COLOR_GREEN, COLOR_BLACK);
	init_pair(2, COLOR_RED, COLOR_BLACK);
	init_pair(3, COLOR_BLUE, COLOR_BLACK);
	init_pair(4, COLOR_CYAN, COLOR_BLACK);
	init_pair(10, COLOR_BLACK, COLOR_WHITE);
	init_pair(11, COLOR_BLACK, COLOR_GREEN);
	init_pair(12, COLOR_BLACK, COLOR_RED);
	init_pair(13, COLOR_BLACK, COLOR_BLUE);
	init_pair(14, COLOR_BLACK, COLOR_CYAN);
	refresh();
}

int		graph_cycle(t_tool *tool)
{
	MEVENT	event;
	int		ch;

	ch = getch();
	if (ch == 27)
		return (1);
	if (ch == ' ')
		tool->e_status = RUN;
	else if (ch == KEY_MOUSE)
	{
		if (getmouse(&event) == OK)
			;
	}
	return (0);
}

void	visual(t_tool *tool)
{
	draw(tool);
	while (tool->e_status == PAUSE)
	{
		if (graph_cycle(tool) == 1)
		{
			delwin(tool->main_win);
			delwin(tool->side_win);
			endwin();
			exit(1);
		}
	}
}
