/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   additional_funcs.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abibyk <abibyk@student.unit.ua>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/27 16:16:36 by abibyk            #+#    #+#             */
/*   Updated: 2018/12/27 17:31:30 by dkotlyar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

int		thanks_norm(char **s1, char **s2)
{
	ft_strdel(s1);
	ft_strdel(s2);
	return (2);
}

void	print_byte_values(uint8_t byte_size, uint32_t val)
{
	uint8_t	*p;
	uint8_t	i;

	if (byte_size == 1)
	{
		ft_printf("%-18u", (uint8_t)val);
		return ;
	}
	p = (uint8_t *)&val;
	i = 0;
	while (byte_size > i)
	{
		ft_printf("%-4u", *p);
		i++;
		p++;
	}
	if (byte_size == 4)
		ft_printf("%2");
	else if (byte_size == 2)
		ft_printf("%10");
}

int		is_line_a_label(char *line)
{
	int	check;

	check = 0;
	if (ft_strchr(line, ':') && (!ft_strchr(line, '%') ||
ft_strchr(line, '%') > ft_strchr(line, ':')))
		check++;
	if (ft_strchr(line, ':') && (!ft_strchr(line, ' ') ||
ft_strchr(line, ' ') > ft_strchr(line, ':')))
		check++;
	if (ft_strchr(line, ':') && (!ft_strchr(line, '\t') ||
ft_strchr(line, '\t') > ft_strchr(line, ':')))
		check++;
	return (check == 3 ? 1 : 0);
}

void	print_labels(t_b_token *b_tokens)
{
	t_b_token	*tmp;
	int			i;

	tmp = b_tokens;
	i = 0;
	while (tmp->labels[i])
		ft_printf("%-5i%7 :    %s\n", b_tokens->bytepos, tmp->labels[i++]);
}
