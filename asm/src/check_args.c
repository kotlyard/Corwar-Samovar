/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_args.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abibyk <abibyk@student.unit.ua>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/24 19:30:11 by abibyk            #+#    #+#             */
/*   Updated: 2018/12/24 19:30:18 by abibyk           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

void	err_msg(char *token, char *instruction, int num, int i)
{
	if (i == 1)
		ft_printf(CLR_RED"ERROR:"CLR_RST"Syntax error at "
			"token instruction \"%s\"\n", token);
	else if (i == 2)
		ft_printf(CLR_RED"ERROR:""Lexical error at "
			"instruction \"%s\"\n", instruction);
	else if (i == 4)
		ft_printf("ERROR:""Syntax error at "
			"instruction \"%s\" SEPARATOR \",\"\n", instruction);
	else
		ft_printf("ERROR:""Invalid parameter "
			"%i type indirect for instruction \"%s\"\n", num, instruction);
	exit(1);
}

int		check_dir(char *args, char *instr, int num)
{
	int i;

	i = 0;
	if (args[i] == '\0')
		err_msg(args, instr, num, 4);
	if (args[i++] != '%')
		err_msg(args, instr, num, 0);
	if (args[i] == ':')
		return (0);
	if (args[i] == '-')
		i++;
	if (args[i] == '\0')
		err_msg(args, instr, num, 2);
	while (args[i])
	{
		if (ft_isdigit(args[i]) == 0)
			err_msg(args, instr, num, 1);
		i++;
	}
	return (0);
}

int		check_ind(char *args, char *instr, int num)
{
	int i;

	i = 0;
	if (args[i] == '\0')
		err_msg(args, instr, num, 4);
	if (args[i] == '-')
		i++;
	if (args[i] == ':')
		return (0);
	if (args[i] == '\0')
		err_msg(args, instr, num, 2);
	while (args[i])
	{
		if (ft_isdigit(args[i]) == 0)
			err_msg(args, instr, num, 0);
		i++;
	}
	return (0);
}

int		check_reg(char *args, char *instr, int num)
{
	int i;

	i = 0;
	if (args[i] == '\0')
		err_msg(args, instr, num, 4);
	if (args[i++] != 'r')
		err_msg(args, instr, num, 2);
	if (args[i] == '\0')
		err_msg(args, instr, num, 1);
	while (args[i])
	{
		if (ft_isdigit(args[i]) == 0)
			err_msg(args, instr, num, 1);
		i++;
	}
	return (0);
}
