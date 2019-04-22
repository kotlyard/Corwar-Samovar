/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dkotlyar <dkotlyar@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/24 16:49:05 by dkotlyar          #+#    #+#             */
/*   Updated: 2018/12/27 15:22:43 by dkotlyar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

char	is_label(char const *str)
{
	int		i;
	size_t	len;

	len = ft_strlen(str);
	if (len == 1)
	{
		ft_printf(CLR_RED"ERROR"CLR_RST
		":Lexical error in line [%s].\n", str);
		exit(1);
	}
	if (len > 0 && str[len - 1] != LABEL_CHAR)
		return (0);
	i = 0;
	while (str[i + 1])
	{
		if (!is_in_here(str[i], LABEL_CHARS))
		{
			ft_printf(CLR_RED"ERROR"CLR_RST":Symbol"
CLR_GRN" '%c'"CLR_RST"is forbidden in label.\n", str[i]);
			exit(1);
		}
		i++;
	}
	return (1);
}

void	save_header_properly(t_asm *data)
{
	data->header.magic = swap_uint32(COREWAR_EXEC_MAGIC);
	if (!data->name || !data->comment)
		print_error("Champion must have both name and comment", -1);
	if (ft_strlen(data->name) > PROG_NAME_LENGTH)
		print_error("Champion name is too long (128 chars is max)", -1);
	if (ft_strlen(data->comment) > COMMENT_LENGTH)
		print_error("Champion comment is too long (2048 chars is max)", -1);
	ft_memset(data->header.prog_name, 0, PROG_NAME_LENGTH + 4);
	ft_memset(data->header.comment, 0, COMMENT_LENGTH + 4);
	ft_strcpy(data->header.prog_name, data->name);
	ft_strcpy(data->header.comment, data->comment);
	ft_strdel(&data->name);
	ft_strdel(&data->comment);
}

int		main(int ac, char **av)
{
	t_asm	data;
	int		fd;

	fd = (int)init_all_and_check_basic_errors(&data, ac, av);
	data.lines = read_file_and_return_strarr(fd, &data);
	get_header(&data);
	save_header_properly(&data);
	data.lines_without_meta = clean_str_arr_from_trash(data.lines,
	data.lines_to_skip);
	tokenize_commands(&data);
	if (!data.tokens)
		print_error("No executable code", -1);
	err_manage(data.tokens);
	data.b_tokens = b_tokenize(&data);
	if (!data.flag)
	{
		create_file(&data);
		ft_printf(CLR_GRN"Writing output program to %s\n"CLR_RST,
		data.file_name);
	}
	else
		flag_processing(&data);
	return (0);
}
