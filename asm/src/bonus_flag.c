/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bonus_flag.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abibyk <abibyk@student.unit.ua>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/26 16:02:18 by abibyk            #+#    #+#             */
/*   Updated: 2018/12/27 16:12:05 by abibyk           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

void	print_first_line(t_token *tokens, t_b_token *b_tokens)
{
	int i;
	int byte_size;

	i = -1;
	ft_printf("%-5i", g_tab[tokens->op_id].op_id);
	if (b_tokens->arg_code > 0)
		ft_printf("%-6u", b_tokens->arg_code);
	else
		ft_printf("%6");
	while (++i < g_tab[tokens->op_id].arg_num)
	{
		if (*tokens->args[i] == '%' || *tokens->args[i] == 'r')
		{
			if (*tokens->args[i] == '%')
			{
				byte_size = g_tab[tokens->op_id].dir_size;
				print_byte_values((u_int8_t)byte_size,
				(uint32_t)b_tokens->args_value[i].value);
			}
			else
				print_byte_values(1, (uint32_t)b_tokens->args_value[i].value);
		}
		else
			print_byte_values(2, (uint32_t)b_tokens->args_value[i].value);
	}
}

void	print_second_line(t_token *tokens, t_b_token *b_tokens)
{
	int i;
	int byte_size;

	i = -1;
	ft_printf("\n%20");
	ft_printf("%-5i", g_tab[tokens->op_id].op_id);
	if (b_tokens->arg_code > 0)
		ft_printf("%-6u", b_tokens->arg_code);
	else
		ft_printf("%6");
	while (++i < g_tab[tokens->op_id].arg_num)
	{
		if (*tokens->args[i] == '%')
		{
			byte_size = g_tab[tokens->op_id].dir_size;
			if (byte_size == 2 || b_tokens->args_value[i].arg_type == IND_CODE)
				ft_printf("%-18hd",
				swap_uint16((uint16_t)b_tokens->args_value[i].value));
			else
				ft_printf("%-18d", swap_uint32(b_tokens->args_value[i].value));
		}
		else
			ft_printf("%-18li", b_tokens->args_value[i].value);
	}
	ft_printf("\n\n");
}

void	print_intro(t_asm *data)
{
	ft_printf("Dumping annotated program on standard output\n");
	ft_printf("Program size : %u bytes\n", swap_uint32(data->header.prog_size));
	ft_printf("Name : \"%s\"\n", data->header.prog_name);
	ft_printf("Comment : \"%s\"\n\n", data->header.comment);
}

void	print_instruction(t_token *tokens, t_b_token *b_tokens, int i)
{
	if (b_tokens->labels)
		print_labels(b_tokens);
	ft_printf("%-5i(%-3i) :        %-10s ", b_tokens->bytepos,
			b_tokens->bytelen, g_tab[tokens->op_id].op_name);
	while (++i < g_tab[tokens->op_id].arg_num)
		ft_printf("%-18s", tokens->args[i]);
}

void	flag_processing(t_asm *data)
{
	t_token		*tokens;
	t_b_token	*b_tokens;
	t_string	*string;
	int			i;

	tokens = data->tokens;
	b_tokens = data->b_tokens;
	string = data->label_list;
	print_intro(data);
	while (tokens)
	{
		i = -1;
		print_instruction(tokens, b_tokens, i);
		ft_printf("\n%20");
		print_first_line(tokens, b_tokens);
		print_second_line(tokens, b_tokens);
		tokens = tokens->next;
		b_tokens = b_tokens->next;
	}
	while (string)
	{
		ft_printf("%-5i%7 :    %s\n",
		swap_uint32(data->header.prog_size), string->line);
		string = string->next;
	}
}
