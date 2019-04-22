/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenize.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dkotlyar <dkotlyar@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/24 19:33:05 by dkotlyar          #+#    #+#             */
/*   Updated: 2018/12/27 16:26:18 by dkotlyar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

int		is_command(char *str, t_op *op_tab)
{
	int	i;

	i = -1;
	while (++i < 16)
	{
		if (ft_strnequ(str, op_tab[i].op_name, ft_strlen(op_tab[i].op_name)))
		{
			if (ft_strnequ(str, "sti", 3))
				if (str[3] && (str[3] == ' ' || str[3] == '\t'))
					return (10);
			if ((ft_strnequ(str, "ldi", 3)))
				if (str[3] && (str[3] == ' ' || str[3] == '\t'))
					return (9);
			if ((ft_strnequ(str, "lldi", 4)))
				if (str[4] && (str[4] == ' ' || str[4] == '\t'))
					return (13);
			if (str[ft_strlen(op_tab[i].op_name)] != ' ' &&
			str[ft_strlen(op_tab[i].op_name)] != '\t')
				break ;
			return (i);
		}
	}
	ft_printf(CLR_RED"ERROR:"CLR_RST"Incorrect operation name[%s].\n", str);
	exit(1);
}

void	check_args_for_excess_chars(char **res, char const *str, int arg_num)
{
	int		i;
	char	*tmp;

	i = 0;
	while (res[i])
	{
		tmp = res[i];
		res[i++] = ft_strtrim(tmp);
		ft_strdel(&tmp);
	}
	if (i != arg_num)
	{
		ft_printf(CLR_RED"ERROR:"CLR_RST
		"[%s] operation requires" CLR_GRN" %d "
		CLR_RST"argument(s).", str, arg_num);
		exit(1);
	}
}

char	**split_operation_and_args(char const *str, uint32_t arg_num)
{
	int		i;
	char	**res;

	i = -1;
	if (count_chars(str, ',') != arg_num - 1)
	{
		ft_printf(CLR_RED"Error:"CLR_RST
"Excess delimiters in instruction [%s]", str);
		exit(1);
	}
	while (str[++i])
		if (str[i] == ' ' || str[i] == '\t')
			break ;
	if (!str[i])
	{
		ft_printf(CLR_RED"ERROR:"CLR_RST
		"%s operation requires arguments.", str);
		exit(1);
	}
	res = ft_strsplit(&str[i], SEPARATOR_CHAR);
	check_args_for_excess_chars(res, str, arg_num);
	return (res);
}

void	add_op_to_list(t_asm *data, int op_id, char const *str,
size_t *len)
{
	static t_token	*last;
	t_token			*new;

	new = (t_token*)ft_memalloc(sizeof(t_token));
	new->labels = NULL;
	if (data->label_list)
		new->labels = from_list_to_strarr(data->label_list, (int)*len);
	new->op_id = (uint8_t)op_id;
	new->args = split_operation_and_args(str, g_tab[op_id].arg_num);
	new->next = NULL;
	if (!data->tokens)
		data->tokens = new;
	else
		last->next = new;
	last = new;
	*len = 0;
}

void	tokenize_commands(t_asm *data)
{
	int		i;
	char	*tmp;
	size_t	len;

	len = 0;
	i = -1;
	while (data->lines_without_meta[++i])
	{
		if (is_label(data->lines_without_meta[i]))
		{
			add_to_list(data->lines_without_meta[i], &data->label_list, 0);
			len++;
		}
		else
		{
			tmp = data->lines_without_meta[i];
			if (ch_fuck(tmp) != -1)
			{
				CURR_LINE = mk_magic(tmp, g_tab[ch_fuck(tmp)].op_name);
				ft_strdel(&tmp);
			}
			add_op_to_list(data, is_command(CURR_LINE, g_tab), CURR_LINE, &len);
			data->label_list = NULL;
		}
	}
}
