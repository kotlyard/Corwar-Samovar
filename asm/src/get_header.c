/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tmp.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dkotlyar <dkotlyar@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/24 19:19:14 by dkotlyar          #+#    #+#             */
/*   Updated: 2018/12/24 19:25:24 by dkotlyar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

size_t		save_name(t_asm *data, size_t i, char *where)
{
	if (!ft_strchr(where, '\n'))
		print_error("Unexpected end of file", i);
	if (data->name)
		print_error("Duplicate .name command", i);
	if (!ft_strchr(where, '"'))
		print_error("No quotes in .name command", i);
	where += pass_whitespaces(where, NAME_CMD_STRING) +
	ft_strlen(NAME_CMD_STRING);
	if (ft_strchr(where, '"') != ft_strrchr(where, '"'))
		return (save_without_nl(0, data, where));
	else
		return (save_with_nl(0, data, where, i));
}

size_t		save_comment(t_asm *data, size_t i, char *where)
{
	if (!ft_strchr(where, '\n'))
		print_error("Unexpected end of file", i);
	if (data->comment)
		print_error("Duplicate .comment command", i);
	if (!ft_strchr(where, '"'))
		print_error("No quotes in .comment command", i);
	where += pass_whitespaces(where, COMMENT_CMD_STRING) +
	ft_strlen(COMMENT_CMD_STRING);
	if (ft_strchr(where, '"') != ft_strrchr(where, '"'))
		return (save_without_nl(1, data, where));
	else
		return (save_with_nl(1, data, where, i));
}

void		check_lines_between(char const *str, size_t str_num)
{
	int i;

	i = 0;
	while (str[i] && str[i] != '\n')
	{
		if (str[i] == COMMENT_CHAR)
			break ;
		if (str[i] != ' ' && str[i] != '\t')
			print_error("Lexical error", str_num);
		i++;
	}
}

size_t		get_header(t_asm *data)
{
	size_t	i;

	i = 0;
	while (i < data->file_len && (!data->comment || !data->name))
	{
		if (((ft_strstr(data->lines[i], NAME_CMD_STRING) &&
			!ft_strchr(data->lines[i],
			COMMENT_CHAR)) || (ft_strstr(data->lines[i], NAME_CMD_STRING) <
			ft_strchr(data->lines[i], COMMENT_CHAR))) &&
			ft_strstr(data->lines[i], NAME_CMD_STRING))
			i += save_name(data, i, data->lines[i]);
		else if (((ft_strstr(data->lines[i], COMMENT_CMD_STRING) &&
			!ft_strchr(data->lines[i], COMMENT_CHAR)) ||
			(ft_strstr(data->lines[i],
			COMMENT_CMD_STRING) < ft_strchr(data->lines[i], COMMENT_CHAR)))
			&& ft_strstr(data->lines[i], COMMENT_CMD_STRING))
			i += save_comment(data, i, data->lines[i]);
		else
		{
			check_lines_between(data->lines[i], i);
			i++;
			data->lines_to_skip++;
		}
	}
	return (i);
}
