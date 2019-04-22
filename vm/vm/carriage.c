/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   carriage.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vzomber <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/13 14:49:49 by vzomber           #+#    #+#             */
/*   Updated: 2018/11/13 14:49:50 by vzomber          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

/*
** Checks carriages for being alive
** if carg is alive -> alive = 0
** else kill it
*/

void	check_alive_cargs(t_tool *tool)
{
	t_carriage	*carg;
	int			i;

	kill_carriages(tool);
	carg = tool->carriages;
	while (carg)
	{
		if (carg->alive == 1)
			carg->alive = 0;
		carg = carg->next;
	}
	i = -1;
	while (++i < 4)
		tool->pl_arr[i].alive = 0;
}

/*
** Frees memory from being used for carriages.
** Kills from 'head'.
*/

void	show_death(t_carriage *carg, t_tool *tool)
{
	ft_printf("Process %d hasn't lived for %d cycles (CTD %d)\n",
			carg->carg_numb, tool->cycles - carg->born,
			tool->cycles_to_die);
}

void	kill_carriages(t_tool *tool)
{
	t_carriage	*tmp;
	t_carriage	*i;

	while (tool->carriages && (tool->carriages->alive == 0))
	{
		ft_strchr(tool->output, 'e') ? show_death(tool->carriages, tool) : 0;
		tmp = tool->carriages;
		tool->carriages = tool->carriages->next;
		free(tmp);
		tool->carg_qty--;
	}
	i = tool->carriages;
	while (i && i->next)
	{
		if (i->next->alive == 0)
		{
			ft_strchr(tool->output, 'e') ? show_death(i->next, tool) : 0;
			tmp = i->next;
			i->next = tmp->next;
			free(tmp);
			tool->carg_qty--;
		}
		else
			i = i->next;
	}
}

/*
** Makes new carriages and adds it to the list.
*/

void	make_carriage(int pl_id, t_tool *tool, int pos)
{
	t_carriage	*carriage;

	pos = MEM(pos);
	CHECK((carriage = (t_carriage*)ft_memalloc(sizeof(t_carriage))));
	if (!tool->carriages)
	{
		tool->carriages = carriage;
		carriage->next = NULL;
	}
	else
	{
		carriage->next = tool->carriages;
		tool->carriages = carriage;
	}
	carriage->carg_numb = ++(tool->carg_number);
	carriage->curr_place = pos;
	carriage->pl_id = pl_id;
	carriage->alive = 0;
	carriage->born = tool->cycles;
	carriage->cmd = tool->map[pos];
}
