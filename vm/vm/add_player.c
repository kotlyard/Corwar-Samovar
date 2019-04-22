/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   add_player.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vzomber <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/10 13:54:08 by vzomber           #+#    #+#             */
/*   Updated: 2018/11/10 13:54:12 by vzomber          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

void			read_name(t_player *player, int fd, t_tool *tool)
{
	unsigned char	header[4];
	unsigned int	tmp;

	if (read(fd, header, 4) != 4)
		err_exit("i can`t read this", tool);
	tmp = (header[1] << 16) | (header[2] << 8) | header[3];
	if (tmp != COREWAR_EXEC_MAGIC)
		err_exit("header is wrong", tool);
	if (read(fd, player->name, PROG_NAME_LENGTH) != PROG_NAME_LENGTH)
		err_exit("i can`t read this or name is wrong", tool);
	player->name[PROG_NAME_LENGTH] = '\0';
}

/*
** Gets player executable code's size.
** All functions in this file read and parse info from 'player.cor'-file.
** Name, comment, exe-code ...
*/

unsigned int	shift_size(char c1, char c2, char c3, char c4)
{
	int				i;
	unsigned char	a[5];
	unsigned int	res;

	a[0] = (unsigned char)c1;
	a[1] = (unsigned char)c2;
	a[2] = (unsigned char)c3;
	a[3] = (unsigned char)c4;
	a[4] = '\0';
	i = -1;
	res = 0;
	while (++i < 4)
		res = (res << 8) | a[i];
	return (res);
}

void			read_comm(t_player *player, int fd, t_tool *tool)
{
	char			str[4];
	char			size[4];
	char			null[4];

	ft_bzero(&str, sizeof(char) * 4);
	ft_bzero(&size, sizeof(char) * 4);
	ft_bzero(&null, sizeof(char) * 4);
	if (read(fd, null, 4) != 4 || !ft_strequ((const char *)null, str))
		err_exit("null is not null", tool);
	if (read(fd, size, 4) != 4)
		err_exit("something bad happened with size", tool);
	if (read(fd, player->comment, COMMENT_LENGTH) != COMMENT_LENGTH)
		err_exit("comment is incorrect", tool);
	player->comment[COMMENT_LENGTH] = '\0';
	player->size = shift_size(size[0], size[1], size[2], size[3]);
	if (read(fd, null, 4) != 4 || !ft_strequ((const char *)null, str))
		err_exit("null is not null", tool);
}

/*
** Number is flexible, index in arr is => 0 && < 4.
*/

t_player		add_player(char *av, t_tool *tool, int numb, int id)
{
	int				fd;
	t_player		player;
	unsigned char	*tmp;

	tmp = (unsigned char*)ft_memalloc(sizeof(unsigned char)
		* MAX_SIZE + 1);
	if ((fd = open(av, O_RDONLY)) < 0)
		err_exit_d("i don`t like that fd:", fd);
	ft_bzero(&player, sizeof(t_player));
	read_name(&player, fd, tool);
	read_comm(&player, fd, tool);
	read(fd, tmp, CHAMP_MAX_SIZE);
	if (player.size == 0 || player.size > CHAMP_MAX_SIZE)
		err_exit("wrong size", tool);
	player.id = id;
	player.numb = numb;
	ft_memcpy(&tool->map[tool->pl_shift * id], tmp, (size_t)player.size);
	make_carriage(player.id, tool, tool->pl_shift * id);
	tool->carriages->reg[1] = (unsigned int)numb;
	tool->carg_qty++;
	free(tmp);
	return (player);
}
