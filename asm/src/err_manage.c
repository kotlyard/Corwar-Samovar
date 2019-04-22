/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   err_manage.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abibyk <abibyk@student.unit.ua>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/24 19:19:45 by abibyk            #+#    #+#             */
/*   Updated: 2018/12/24 19:24:10 by abibyk           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

void	check_sti(char **args, char *instr)
{
	check_reg(args[0], instr, 0);
	if (*args[1] == 'r')
		check_reg(args[1], instr, 1);
	else if (*args[1] == '%')
		check_dir(args[1], instr, 1);
	else
		check_ind(args[1], instr, 1);
	*args[2] == '%' ? check_dir(args[2], instr, 2) :
	check_reg(args[2], instr, 2);
}

void	check_ldi(char **args, char *instr)
{
	if (*args[0] == 'r')
		check_reg(args[0], instr, 0);
	else if (*args[0] == '%')
		check_dir(args[0], instr, 0);
	else
		check_ind(args[0], instr, 0);
	*args[1] == 'r' ? check_reg(args[1], instr, 1) :
	check_dir(args[1], instr, 1);
	check_reg(args[2], instr, 2);
}

void	check_and_or_xor(char **args, char *instr)
{
	if (*args[0] == 'r')
		check_reg(args[0], instr, 0);
	else if (*args[0] == '%')
		check_dir(args[0], instr, 0);
	else
		check_ind(args[0], instr, 0);
	if (*args[1] == 'r')
		check_reg(args[1], instr, 1);
	else if (*args[1] == '%')
		check_dir(args[1], instr, 1);
	else
		check_ind(args[1], instr, 1);
	check_reg(args[2], instr, 2);
}

void	check_rest(char **args, char *instr)
{
	if (ft_strequ(instr, "add") || ft_strequ(instr, "sub"))
	{
		check_reg(args[0], instr, 0);
		check_reg(args[1], instr, 1);
		check_reg(args[2], instr, 2);
	}
	else if (ft_strequ(instr, "st"))
	{
		check_reg(args[0], instr, 0);
		*args[1] == 'r' ? check_reg(args[1], instr, 1) :
			check_ind(args[1], instr, 1);
	}
	else if (ft_strequ(instr, "ld") || ft_strequ(instr, "lld"))
	{
		*args[0] == '%' ? check_dir(args[0], instr, 0) :
			check_ind(args[0], instr, 0);
		check_reg(args[1], instr, 1);
	}
}

void	err_manage(t_token *op_list)
{
	t_token *tmp;

	tmp = op_list;
	while (tmp)
	{
		if (ft_strequ(g_tab[tmp->op_id].op_name, "live") ||
			ft_strequ(g_tab[tmp->op_id].op_name, "zjmp") ||
			ft_strequ(g_tab[tmp->op_id].op_name, "fork") ||
			ft_strequ(g_tab[tmp->op_id].op_name, "lfork"))
			check_dir(tmp->args[0], g_tab[tmp->op_id].op_name, 0);
		else if (ft_strequ(g_tab[tmp->op_id].op_name, "and") ||
				ft_strequ(g_tab[tmp->op_id].op_name, "or") ||
				ft_strequ(g_tab[tmp->op_id].op_name, "xor"))
			check_and_or_xor(tmp->args, g_tab[tmp->op_id].op_name);
		else if (ft_strequ(g_tab[tmp->op_id].op_name, "ldi") ||
				ft_strequ(g_tab[tmp->op_id].op_name, "lldi"))
			check_ldi(tmp->args, g_tab[tmp->op_id].op_name);
		else if (ft_strequ(g_tab[tmp->op_id].op_name, "sti"))
			check_sti(tmp->args, g_tab[tmp->op_id].op_name);
		else if (ft_strequ(g_tab[tmp->op_id].op_name, "aff"))
			check_reg(tmp->args[0], g_tab[tmp->op_id].op_name, 0);
		else
			check_rest(tmp->args, g_tab[tmp->op_id].op_name);
		tmp = tmp->next;
	}
}
