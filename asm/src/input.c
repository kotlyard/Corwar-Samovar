/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dkotlyar <dkotlyar@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/23 20:48:59 by dkotlyar          #+#    #+#             */
/*   Updated: 2018/12/24 16:33:12 by dkotlyar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

char		**read_file_and_return_strarr(ssize_t fd, t_asm *data)
{
	int			len;
	char		*line;
	t_string	*list;

	len = 0;
	list = NULL;
	while (get_next_line((int)fd, &line) > 0)
	{
		add_to_list(line, &list, 0);
		len++;
		ft_strdel(&line);
	}
	if (!len)
		print_error("Invalid argument (next time do not send directory)", -1);
	if (len < 3)
		print_error("Not enough data", -1);
	ft_strdel(&line);
	data->file_len = (uint32_t)len;
	return (from_list_to_strarr(list, len));
}

t_string	*clean_from_comment(t_string *list)
{
	char		*tmp;
	t_string	*head;

	head = list;
	while (list)
	{
		if (ft_strchr(list->line, COMMENT_CHAR))
		{
			tmp = ft_strsub(list->line, 0,
			ft_strchr(list->line, COMMENT_CHAR) - list->line);
			ft_strdel(&list->line);
			list->line = ft_strtrim(tmp);
			ft_strdel(&tmp);
		}
		list = list->next;
	}
	return (head);
}

void		check_for_nl(char const *str, size_t num, char is_nl)
{
	long	i;
	int		check;
	char	is_comment;

	check = 0;
	i = -1;
	is_comment = 0;
	if (ft_strlen(str) > 0 && str[ft_strlen(str) - 1] == '\n')
		is_nl = 1;
	while (str[++i])
	{
		if (str[i] == COMMENT_CHAR)
		{
			is_comment = 1;
			break ;
		}
		if (str[i] != '\t' && str[i] != ' ' && str[i] != '\n')
			check++;
	}
	if ((is_comment == 1 && check == 0) ||
		(is_comment == 1 && check > 0 && is_nl == 1))
		return ;
	if (check > 0 && !is_nl)
		print_error("Unexpected end of file", num);
}

char		**clean_str_arr_from_trash(char **lines, size_t start)
{
	int			len;
	char		*tmp;
	t_string	*list;
	t_string	*res;

	len = 0;
	list = NULL;
	while (lines[start])
	{
		check_for_nl(lines[start], start, 0);
		tmp = ft_strtrim(lines[start]);
		if (tmp && !ft_strequ(tmp, "") && ft_strchr(tmp, COMMENT_CHAR) != tmp)
		{
			add_to_list(tmp, &list, 1);
			len++;
		}
		ft_strdel(&tmp);
		start++;
	}
	clean_from_comment(list);
	res = cut_labels(list, &len);
	free_list(list);
	return (from_list_to_strarr(res, len));
}
