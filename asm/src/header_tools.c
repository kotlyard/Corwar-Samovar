/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   header_tools.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dkotlyar <dkotlyar@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/24 16:26:35 by dkotlyar          #+#    #+#             */
/*   Updated: 2018/12/24 16:32:13 by dkotlyar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

size_t		check_symbols_around_quotes(char const *start, uint8_t b_or_a)
{
	size_t i;

	i = b_or_a;
	if (!b_or_a)
	{
		while (start[i] && start[i] != '\"')
		{
			if (start[i] != ' ' && start[i] != '\t')
				print_error("Invalid symbol before quotes", -1);
			i++;
		}
		return (i);
	}
	while (start[i] && start[i] != '\n' && start[i] != COMMENT_CHAR)
	{
		if (start[i] != ' ' && start[i] != '\t')
			print_error("Invalid symbol after quotes", -1);
		i++;
	}
	return (i);
}

void		add_to_name_or_comment(char is_comment,
t_asm *data, char const *str)
{
	char	*tmp;

	tmp = ft_strjoin(is_comment ? data->comment : data->name, str);
	ft_strdel(is_comment ? &data->comment : &data->name);
	if (is_comment)
		data->comment = tmp;
	else
		data->name = tmp;
}

size_t		save_with_nl(char is_comment, t_asm *data,
char const *start, size_t i)
{
	size_t	j;
	char	*tmp;
	char	*close;

	j = (unsigned)check_symbols_around_quotes(start, 0) + 1;
	if (is_comment)
		data->comment = ft_strsub(start, j, ft_strlen(start) - j);
	else
		data->name = ft_strsub(start, j, ft_strlen(start) - j);
	j = i + 1;
	while (data->lines[j] && !(close = ft_strchr(data->lines[j], '"')))
	{
		add_to_name_or_comment(is_comment, data, data->lines[j++]);
		data->lines_to_skip++;
	}
	if (!close)
		print_error("No closing quotes", -1);
	if (!ft_strchr(close, '\n'))
		print_error("Unexpected end of file", j);
	tmp = ft_strsub(data->lines[j], 0, close - data->lines[j]);
	add_to_name_or_comment(is_comment, data, tmp);
	data->lines_to_skip += 2;
	check_symbols_around_quotes(close, 1);
	ft_strdel(&tmp);
	return (j - i + 1);
}

size_t		save_without_nl(char is_comment, t_asm *data, char *start)
{
	size_t	j;
	size_t	begin;

	j = check_symbols_around_quotes(start, 0) + 1;
	begin = j;
	while (start[j] && start[j] != '"')
		j++;
	check_symbols_around_quotes(&start[j], 1);
	if (is_comment)
		data->comment = ft_strsub(start, (unsigned)begin, j - begin);
	else
		data->name = ft_strsub(start, (unsigned)begin, j - begin);
	data->lines_to_skip++;
	return (1);
}

unsigned	pass_whitespaces(char *str, char const *what)
{
	char		*p_to_command;
	unsigned	i;

	p_to_command = ft_strstr(str, what);
	i = 0;
	while (str[i] && &str[i] != p_to_command)
	{
		if (str[i] != ' ' && str[i] != '\t')
			print_error("Invalid symbols before .name/.comment command", -1);
		i++;
	}
	return (i);
}
