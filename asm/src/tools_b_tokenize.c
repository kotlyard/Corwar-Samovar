/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools_b_tokenize.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dkotlyar <dkotlyar@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/24 20:31:27 by dkotlyar          #+#    #+#             */
/*   Updated: 2018/12/27 15:39:13 by dkotlyar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

uint32_t	count_chars(char const *str, char c)
{
	uint32_t res;
	uint32_t i;

	res = 0;
	i = 0;
	while (str[i])
		if (str[i++] == c)
			res++;
	return (res);
}

uint8_t		get_arg_size(char c)
{
	if (c == 'r')
		return (1);
	if (c == '%')
		return (2);
	if (ft_isdigit(c) || c == '-' || c == ':')
		return (3);
	return (0);
}

char		is_ref_to_end(char const *ref, t_string *label_list)
{
	t_string *list;

	list = label_list;
	while (list)
	{
		if (ft_strnequ(ref, list->line, ft_strlen(ref)) &&
			list->line[ft_strlen(ref)] == ':')
			return (1);
		list = list->next;
	}
	return (0);
}

uint32_t	find_reference(t_b_token *head, char const *ref,
uint32_t ref_to_end, t_string *label_list)
{
	t_b_token	*tmp;
	int			i;

	tmp = head;
	while (tmp)
	{
		i = -1;
		if (tmp->labels)
		{
			while (tmp->labels[++i])
				if (ft_strnequ(ref, tmp->labels[i], ft_strlen(ref)) &&
				tmp->labels[i][ft_strlen(ref)] == ':')
					return (tmp->bytepos);
		}
		tmp = tmp->next;
	}
	if (is_ref_to_end(ref, label_list))
		return (ref_to_end);
	ft_printf(CLR_RED"Error:"CLR_RST"Reference to nonexistent label:%s\n", ref);
	exit(1);
}

void		set_references(t_b_token *head, t_asm *data)
{
	t_b_token	*tmp;
	int			i;
	uint32_t	pref;

	tmp = head;
	while (tmp)
	{
		i = -1;
		while (++i < tmp->arg_num)
		{
			if (tmp->args_value[i].arg_type != REG_CODE &&
				tmp->args_value[i].reference)
			{
				pref = find_reference(head, tmp->args_value[i].reference,
				data->ref_to_last, data->label_list);
				tmp->args_value[i].value = pref - tmp->bytepos;
				tmp->args_value[i].value = (tmp->dir_size == 4 &&
				tmp->args_value[i].arg_type == DIR_CODE ?
				swap_uint32(tmp->args_value[i].value) :
				swap_uint16((uint16_t)tmp->args_value[i].value));
			}
		}
		tmp = tmp->next;
	}
}
