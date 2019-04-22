/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vzomber <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/10 15:45:51 by vzomber           #+#    #+#             */
/*   Updated: 2018/11/10 15:45:52 by vzomber          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

void	dump_map(t_tool *tool)
{
	int	i;
	int	j;

	i = -1;
	while (++i < 64)
	{
		j = -1;
		ft_printf("0x%.4x : ", i * 64);
		while (++j < 64)
			ft_printf("%.2x ", tool->map[i * 64 + j]);
		ft_printf("\n");
	}
}

void	stop_visual(t_tool *tool)
{
	if (tool->visual)
	{
		end_game(tool);
		while (1)
			if (getch() == 32)
			{
				delwin(tool->main_win);
				delwin(tool->side_win);
				endwin();
				exit(1);
			}
	}
}

void	err_exit_d(char *str, int num)
{
	ft_printf("%s %d\n", str, num);
	exit(1);
}

void	err_exit(char *str, t_tool *tool)
{
	ft_printf("%s\n", str);
	tool->visual ? stop_visual(tool) : 0;
	exit(1);
}

void	visual_on(t_tool *tool)
{
	tool->visual = 1;
	tool->dump = 0;
	tool->output = "";
}
