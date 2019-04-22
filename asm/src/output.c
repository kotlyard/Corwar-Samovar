/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   output.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dkotlyar <dkotlyar@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/24 19:27:24 by dkotlyar          #+#    #+#             */
/*   Updated: 2018/12/27 19:42:49 by dkotlyar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

char		*get_output_file_name(char *str)
{
	char	*res;
	char	*tmp;

	if (ft_strrchr(str, '.'))
		tmp = ft_strsub(str, 0, ft_strrchr(str, '.') - str);
	else
		tmp = ft_strdup(str);
	res = ft_strjoin(tmp, ".cor");
	ft_strdel(&tmp);
	return (res);
}

uint16_t	swap_uint16(uint16_t val)
{
	return (val << 8) | (val >> 8);
}

uint32_t	swap_uint32(uint32_t val)
{
	val = ((val << 8) & 0xFF00FF00) | ((val >> 8) & 0xFF00FF);
	return (val << 16) | (val >> 16);
}

t_b_token	*precreate_file(t_asm *data, int fd)
{
	write(fd, &data->header.magic, sizeof(uint32_t));
	write(fd, &data->header.prog_name, PROG_NAME_LENGTH + 4);
	write(fd, &data->header.prog_size, sizeof(uint32_t));
	write(fd, &data->header.comment, COMMENT_LENGTH + 4);
	return (data->b_tokens);
}

void		create_file(t_asm *data)
{
	int			fd;
	int			i;
	t_b_token	*tmp;

	if ((fd = open(data->file_name, O_WRONLY | O_CREAT | O_TRUNC, 0666)) == -1)
		print_error("Open for output file failed", -1);
	tmp = precreate_file(data, fd);
	while (tmp)
	{
		write(fd, &tmp->op_code, sizeof(uint8_t));
		if (tmp->arg_code != 0)
			write(fd, &tmp->arg_code, sizeof(uint8_t));
		i = -1;
		while (++i < tmp->arg_num)
		{
			if (tmp->args_value[i].arg_type == REG_CODE)
				write(fd, &tmp->args_value[i].value, sizeof(uint8_t));
			else if (tmp->args_value[i].arg_type == IND_CODE ||
				(tmp->args_value[i].arg_type == T_DIR && tmp->dir_size == 2))
				write(fd, &tmp->args_value[i].value, sizeof(uint16_t));
			else
				write(fd, &tmp->args_value[i].value, sizeof(uint32_t));
		}
		tmp = tmp->next;
	}
}
