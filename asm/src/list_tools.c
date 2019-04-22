/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list_tools.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dkotlyar <dkotlyar@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/24 16:47:58 by dkotlyar          #+#    #+#             */
/*   Updated: 2018/12/24 16:48:49 by dkotlyar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

void	free_list(t_string *list)
{
	t_string *tmp;

	while (list)
	{
		tmp = list;
		list = list->next;
		ft_strdel(&tmp->line);
		free(tmp);
	}
}

char	**from_list_to_strarr(t_string *list, int len)
{
	char		**res;
	t_string	*tmp;
	int			i;

	i = 0;
	tmp = list;
	res = (char**)ft_memalloc(sizeof(char*) * (len + 1));
	while (tmp)
	{
		res[i] = ft_strdup(tmp->line);
		tmp = tmp->next;
		i++;
	}
	res[i] = NULL;
	free_list(list);
	return (res);
}

void	add_to_list(char *line, t_string **list, char to_trim)
{
	t_string		*new;
	static t_string	*last;

	new = (t_string*)ft_memalloc(sizeof(t_string));
	new->line = (to_trim ? ft_strtrim(line) : ft_strdup(line));
	new->next = NULL;
	if (!*list)
		*list = new;
	else
		last->next = new;
	last = new;
}
