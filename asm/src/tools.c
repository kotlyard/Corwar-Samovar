/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dkotlyar <dkotlyar@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/24 16:51:53 by dkotlyar          #+#    #+#             */
/*   Updated: 2018/12/27 17:30:28 by dkotlyar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

t_op		g_tab[17] =
{
	{"live", 1, {T_DIR}, 1, 0, 4},
	{"ld", 2, {T_DIR | T_IND, T_REG}, 2, 1, 4},
	{"st", 2, {T_REG, T_IND | T_REG}, 3, 1, 4},
	{"add", 3, {T_REG, T_REG, T_REG}, 4, 1, 4},
	{"sub", 3, {T_REG, T_REG, T_REG}, 5, 1, 4},
	{"and", 3, {T_REG | T_DIR | T_IND, T_REG | T_IND | T_DIR, T_REG}, 6, 1, 4},
	{"or", 3, {T_REG | T_IND | T_DIR, T_REG | T_IND | T_DIR, T_REG}, 7, 1, 4},
	{"xor", 3, {T_REG | T_IND | T_DIR, T_REG | T_IND | T_DIR, T_REG}, 8, 1, 4},
	{"zjmp", 1, {T_DIR}, 9, 0, 2},
	{"ldi", 3, {T_REG | T_DIR | T_IND, T_DIR | T_REG, T_REG}, 10, 1, 2},
	{"sti", 3, {T_REG, T_REG | T_DIR | T_IND, T_DIR | T_REG}, 11, 1, 2},
	{"fork", 1, {T_DIR}, 12, 0, 2},
	{"lld", 2, {T_DIR | T_IND, T_REG}, 13, 1, 4},
	{"lldi", 3, {T_REG | T_DIR | T_IND, T_DIR | T_REG, T_REG}, 14, 1, 2},
	{"lfork", 1, {T_DIR}, 15, 0, 2},
	{"aff", 1, {T_REG}, 16, 1, 4},
	{0, 0, {0}, 0, 0, 0}
};

ssize_t		init_all_and_check_basic_errors(t_asm *data, int ac, char **av)
{
	int	fd;
	int i;

	i = 0;
	data->flag = 0;
	if (ac < 2)
		print_error("", 1488);
	while (++i < ac - 1)
		if (ft_strstr(av[i], "-a"))
			data->flag = 1;
	if ((fd = open(av[ac - 1], O_RDONLY)) == -1)
		print_error("Open error", -1);
	data->tokens = NULL;
	data->file_name = get_output_file_name(av[1]);
	data->comment = NULL;
	data->name = NULL;
	data->label_list = NULL;
	data->lines_to_skip = 0;
	return (fd);
}

int			is_in_here(char symb, char *where)
{
	size_t i;

	i = 0;
	while (where[i])
	{
		if (where[i] != symb)
			i++;
		else
			break ;
	}
	return (i == ft_strlen(where) ? 0 : 1);
}

void		print_error(char *msg, ssize_t line_number)
{
	if (line_number == 1488)
		ft_printf(CLR_CYA"Usage:\n"CLR_MAG
		"./asm [-a] [example.s]\n"
CLR_RED"-a "CLR_MAG ": Instead of creating a .cor file, outputs a stripped and "
		"annotated version of the code to the standard output\n"CLR_RST);
	else if (line_number != -1)
		ft_printf(CLR_RED"ERROR:"CLR_RST
		"%s on line %d.\n", msg, line_number + 1);
	else
		ft_printf(CLR_RED"ERROR:"CLR_RST"%s.\n", msg);
	exit(1);
}

char		*get_after(char *str, char *before)
{
	char *after;

	after = ft_strsub(str, (unsigned)(ft_strchr(str,
	':') - str + 1), ft_strlen(str) - ft_strlen(before));
	return (after);
}

t_string	*cut_labels(t_string *list, int *len)
{
	t_string	*new_list;
	t_string	*tmp;
	char		*before;
	char		*after;

	new_list = NULL;
	tmp = list;
	while (tmp)
	{
		if (is_line_a_label(tmp->line))
		{
			before = ft_strsub(tmp->line, 0, ft_strchr(tmp->line, ':') -
tmp->line + 1);
			after = get_after(tmp->line, before);
			add_to_list(before, &new_list, 0);
			if (after && !ft_strequ("", after))
				add_to_list(after, &new_list, 1);
			(*len) += thanks_norm(&before, &after);
		}
		else
			add_to_list(tmp->line, &new_list, 1);
		tmp = tmp->next;
	}
	return (new_list);
}
