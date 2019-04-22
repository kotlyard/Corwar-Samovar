/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dkotlyar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/18 14:39:11 by dkotlyar          #+#    #+#             */
/*   Updated: 2018/10/11 18:04:43 by dkotlyar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# include "libft.h"
# include <fcntl.h>
# define BUFF_SIZE 1000

int					get_next_line(int fd, char **line);

typedef struct		s_gnl
{
	int				fd;
	char			*residue;
	struct s_gnl	*next;
}					t_gnl;

#endif
