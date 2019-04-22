/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   b-tokenize.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dkotlyar <dkotlyar@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/23 20:47:53 by dkotlyar          #+#    #+#             */
/*   Updated: 2018/12/23 20:48:38 by dkotlyar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

uint8_t			save_arg_size(uint8_t op_code, char **args)
{
	uint8_t	res;
	uint8_t	i;
	uint8_t	arg_size;

	i = 0;
	res = 0;
	if (op_code == 1 || op_code == 9 || op_code == 12 || op_code == 15)
		return (res);
	if (op_code == 16)
		return (0x40);
	else
	{
		while (args[i] && i < 3)
		{
			arg_size = get_arg_size(args[i++][0]);
			res |= arg_size;
			res = res << 2;
		}
	}
	if (i == 2)
		res = res << 2;
	return (res);
}

void			save_arg_value(char const *str, t_arg *arg, char dir_size)
{
	if (str[0] == 'r')
	{
		arg->arg_type = REG_CODE;
		arg->value = (uint8_t)ft_atoi(&str[1]);
	}
	else if (str[0] == '%')
	{
		arg->arg_type = DIR_CODE;
		if (str[1] && (ft_isdigit(str[1]) || str[1] == '-'))
		{
			if (dir_size == 2)
				arg->value = swap_uint16((uint16_t)ft_atoi(&str[1]));
			else
				arg->value = swap_uint32((uint32_t)ft_atoi(&str[1]));
		}
		else if (str[1] == ':')
			arg->reference = ft_strsub(str, 2, ft_strlen(str) - 2);
	}
	else
	{
		arg->arg_type = IND_CODE;
		if (str[0] == ':')
			arg->reference = ft_strsub(str, 1, ft_strlen(str) - 1);
		arg->value = swap_uint16((uint16_t)ft_atoi(str));
	}
}

t_b_token		*create_b_token_from_token(t_token *to_add, t_op *ops)
{
	t_b_token	*b_new;
	size_t		i;

	b_new = (t_b_token*)ft_memalloc(sizeof(t_b_token));
	b_new->op_code = (uint8_t)(to_add->op_id + 1);
	b_new->dir_size = ops[to_add->op_id].dir_size;
	b_new->next = NULL;
	b_new->arg_code = save_arg_size(b_new->op_code, to_add->args);
	b_new->bytelen = (b_new->arg_code ? 2 : 1);
	b_new->labels = to_add->labels;
	i = 0;
	while (to_add->args[i])
	{
		b_new->args_value[i].reference = NULL;
		save_arg_value(to_add->args[i], &b_new->args_value[i], b_new->dir_size);
		if (b_new->args_value[i].arg_type == REG_CODE)
			b_new->bytelen += 1;
		else
			b_new->bytelen += (b_new->args_value[i].arg_type ==
			DIR_CODE && b_new->dir_size == 4) ? 4 : 2;
		b_new->arg_num = (uint8_t)++i;
	}
	return (b_new);
}

uint32_t		add_b_token_to_list(t_b_token **list, t_token to_add, t_op *ops)
{
	static t_b_token	*last;
	static uint32_t		prev_pos = 0;
	t_b_token			*new;

	new = create_b_token_from_token(&to_add, ops);
	new->bytepos = prev_pos;
	prev_pos = new->bytepos + new->bytelen;
	if (!*list)
		*list = new;
	else
		last->next = new;
	last = new;
	return (prev_pos);
}

t_b_token		*b_tokenize(t_asm *data)
{
	t_token		*tmp;
	t_b_token	*head;

	head = NULL;
	tmp = data->tokens;
	while (tmp)
	{
		data->header.prog_size = add_b_token_to_list(&head, *tmp, g_tab);
		if (!tmp->next)
			data->ref_to_last = data->header.prog_size;
		tmp = tmp->next;
	}
	data->header.prog_size = swap_uint32(data->header.prog_size);
	set_references(head, data);
	return (head);
}
