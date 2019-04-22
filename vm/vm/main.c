/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vzomber <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/10 12:53:04 by vzomber           #+#    #+#             */
/*   Updated: 2018/11/10 12:53:06 by vzomber          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

void	show_usage(void)
{
	ft_printf("usage: ./corewar [-dump <number_of_cycles>] ");
	ft_printf("[[-n number] player_1.cor] ... [[-n number] player_4.cor]\n");
	ft_printf("############################################################\n");
	ft_printf("#### OUTPUT MODE ###########################################\n");
	ft_printf("#\t-V  \t :Visual output mode\t\t           #\n");
	ft_printf("#\t-v 'chr' :Verbosity levels:\t\t           #\n");
	ft_printf("#\t\t -a : Show only essentials                 #\n");
	ft_printf("#\t\t -b : Show lives                           #\n");
	ft_printf("#\t\t -c : Show cycles                          #\n");
	ft_printf("#\t\t -d : Show operations                      #\n");
	ft_printf("#\t\t -e : Show deaths                          #\n");
	ft_printf("#\t\t -f : Show PC movements (Except for jumps) #\n");
	ft_printf("############################################################\n");
}

int		count_players(int ac, char **av, t_tool *tool)
{
	int	i;
	int	num;

	i = 0;
	num = 0;
	while (++i < ac)
	{
		if (ft_strstr(av[i], ".cor"))
			num++;
	}
	if (num > MAX_PLAYERS)
		err_exit("too many players", tool);
	return (num);
}

void	start_game(t_tool *tool)
{
	int	i;

	i = -1;
	if (tool->visual == 0)
		ft_putendl("Introducing contestants...");
	else
	{
		tool->bold = ft_memalloc(MEM_SIZE);
		tool->colors = ft_memalloc(MEM_SIZE);
	}
	while (++i < tool->pl_qty)
	{
		if (tool->visual == 0)
		{
			ft_printf("* Player %d, weighing %u bytes, \"%s\" (\"%s\") !\n",
					ABS(tool->pl_arr[i].numb), tool->pl_arr[i].size,
					tool->pl_arr[i].name, tool->pl_arr[i].comment);
		}
		else if (tool->visual == 1)
			ft_memset(&tool->colors[tool->pl_shift * tool->pl_arr[i].id],
				tool->pl_arr[i].id + 1,
					(size_t)tool->pl_arr[i].size);
	}
}

void	flags(t_tool *tool, int ac, char **av)
{
	int	i;
	int	id;

	i = 0;
	id = -1;
	while (++i < ac)
	{
		if (ft_strequ(av[i], "-V"))
			visual_on(tool);
		if (ac > i && ft_strequ(av[i], "-v"))
			tool->output = av[i + 1];
		if (!tool->visual && ft_strequ(av[i], "-dump") && ac > i)
			tool->dump = ABS(ft_atoi(av[i + 1]));
		if (ft_strstr(av[i], ".cor"))
		{
			++id;
			if (i > 2 && ft_strequ(av[i - 2], "-n") && ft_atoi(av[i - 1]) > 4)
				tool->pl_arr[id] =
					add_player(av[i], tool, ft_atoi(av[i - 1]), id);
			else
				tool->pl_arr[id] = add_player(av[i], tool, (id + 1) * (-1), id);
		}
	}
}

int		main(int ac, char **av)
{
	t_tool	tool;

	if (ac > 1)
	{
		ft_bzero(&tool, sizeof(t_tool));
		tool.cycles_to_die = CYCLE_TO_DIE;
		tool.pl_qty = count_players(ac, av, &tool);
		if (tool.pl_qty > 1)
			tool.pl_shift = MEM_SIZE / tool.pl_qty;
		if (tool.pl_qty)
		{
			flags(&tool, ac, av);
			start_game(&tool);
			tool.e_status = PAUSE;
			tool.visual ? init_window(&tool) : 0;
			algo(&tool);
			end_of_the_game(&tool);
		}
		else
			err_exit("I can't start game, something wrong.", &tool);
	}
	else
		show_usage();
	return (0);
}
