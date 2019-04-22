/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vm.h                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vzomber <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/09 16:58:23 by vzomber           #+#    #+#             */
/*   Updated: 2018/11/09 16:58:25 by vzomber          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef VM_H
# define VM_H

# include "ft_printf.h"
# include <ncurses.h>
# include <fcntl.h>

# define REG				1
# define IND				2
# define DIR				4
# define DELAY				14000

# define M					MEM_SIZE
# define MEM(x) (((x) % (M)) < 0 ? (((x) % (M)) + (M)) : ((x) % (M)))
# define CHECK(x) if (!x) exit (1)
# define VCHECK(x) if (x) return ;
# define ABS(n) (n < 0 ? -n : n)

# define REG_CODE			1
# define DIR_CODE			2
# define IND_CODE			3

# define MAX_PLAYERS		4
# define MEM_SIZE			(4*1024)
# define IDX_MOD			(MEM_SIZE / 8)
# define CHAMP_MAX_SIZE		(MEM_SIZE / 6)
# define MAX_SIZE			CHAMP_MAX_SIZE * 2
# define REG_NUMBER			16

# define CYCLE_TO_DIE		1536
# define CYCLE_DELTA		50
# define NBR_LIVE			21
# define MAX_CHECKS			10

# define PROG_NAME_LENGTH	(128)
# define COMMENT_LENGTH		(2048)
# define COREWAR_EXEC_MAGIC	0xea83f3

/*
**____________________________________STRUCTS___________________________________
*/

typedef struct			s_args
{
	int					av1;
	int					av2;
	int					av3;
	int					all_len;
}						t_args;

typedef struct			s_carriage
{
	int					curr_place;
	int					carry;
	int					pl_id;
	unsigned int		reg[REG_NUMBER + 1];
	int					alive;
	int					cmd;
	int					cycles_wait;
	int					carg_numb;
	int					born;
	t_args				args;
	int					tmp;
	struct s_carriage	*next;
}						t_carriage;

typedef struct			s_player
{
	char				name[PROG_NAME_LENGTH + 1];
	char				comment[COMMENT_LENGTH + 1];
	unsigned int		size;
	int					id;
	int					numb;
	int					alive;
}						t_player;

typedef struct			s_tool
{
	t_player			pl_arr[4];
	int					pl_shift;
	int					pl_qty;
	int					last;

	int					cycles_to_die;
	int					cycles;

	int					carg_qty;
	int					carg_number;
	t_carriage			*carriages;

	unsigned char		map[MEM_SIZE + 1];

	unsigned char		*colors;
	unsigned char		*bold;
	int					visual;
	char				*output;
	int					dump;
	WINDOW				*main_win;
	WINDOW				*side_win;
	enum
	{
		RUN,
		PAUSE
	}					e_status;
	int					lives;
}						t_tool;

/*
**____________________________________PLAYER____________________________________
*/

t_player				add_player(char *av, t_tool *tool, int numb, int id);
void					set_player_alive(t_tool *tool, int num);
int						get_ind_value(t_tool *tool, int place, int param);
void					algo(t_tool *tool);

/*
**____________________________________ARGS____________________________________
*/

int						argv1(int num);
int						argv2(int num);
int						argv3(int num);
int						get_value(t_tool *tool, int place, int len);

/*
**__________________________________CARRIAGES__________________________________
*/

void					make_carriage(int pl_numb, t_tool *tool, int pos);
void					kill_carriages(t_tool *tool);
int						check_cycles_wait(t_carriage *carg, int cycles);

/*
**____________________________________ERRORS____________________________________
*/

void					err_exit_d(char *str, int num);
void					err_exit(char *str, t_tool *tool);

/*
**__________________________________OPERATIONS__________________________________
*/

void					exe_live(t_carriage *carg, t_tool *tool, int cycles);
void					exe_ld(t_carriage *carg, t_tool *tool, int cycles);
void					exe_st(t_carriage *carg, t_tool *tool, int cycles);
void					exe_add(t_carriage *carg, t_tool *tool, int cycles);
void					exe_sub(t_carriage *carg, t_tool *tool, int cycles);
void					exe_and(t_carriage *carg, t_tool *tool, int cycles);
void					exe_or(t_carriage *carg, t_tool *tool, int cycles);
void					exe_xor(t_carriage *carg, t_tool *tool, int cycles);
void					exe_zjmp(t_carriage *carg, t_tool *tool, int cycles);
void					exe_ldi(t_carriage *carg, t_tool *tool, int cycles);
void					exe_sti(t_carriage *carg, t_tool *tool, int cycles);
void					exe_fork(t_carriage *carg, t_tool *tool, int cycles);
void					exe_lld(t_carriage *carg, t_tool *tool, int cycles);
void					exe_lldi(t_carriage *carg, t_tool *tool, int cycles);
void					exe_lfork(t_carriage *carg, t_tool *tool, int cycles);
void					exe_aff(t_carriage *carg, t_tool *tool, int cycles);
void					skip(t_tool *tool, t_carriage *carg, int len);
int						check_correct_reg(int num1, int num2, int num3);
int						no_code_length(int av1, int av2, int av3);

/*
**____________________________________VISUAL____________________________________
*/

void					visual(t_tool *tool);
void					visual_on(t_tool *tool);
void					stop_visual(t_tool *tool);
void					end_game(t_tool *tool);
WINDOW					*create_newwin(int height, int width, int starty,
														int startx);
int						players(WINDOW *side_win, int line, t_tool *tool);
void					side_panel(WINDOW *side_win, t_tool *tool);
void					main_panel(WINDOW *main_win, t_tool *tool);
int						graph_cycle(t_tool *tool);
void					init_window(t_tool *tool);
void					create_field(t_tool *tool);
void					draw(t_tool *tool);
void					paint_carg(t_tool *tool);
void					write_map_color(t_tool *tool, int pos, int len,
														t_carriage *carg);

/*
**_________________________________USEFUL/LOGS_________________________________
*/

void					print_pc_move(t_tool *tool, t_carriage *carg, int len);
void					dump_map(t_tool *tool);
void					write_map(t_tool *tool, int pos, int src, size_t len);
void					show_death(t_carriage *carg, t_tool *tool);
void					kill_all(t_tool *tool);
void					check_place(t_tool *tool, t_carriage *carg);
int						length(int num, int av1, int av2, int av3);
int						lab_length(int num, int av1, int av2, int av3);
void					end_of_the_game(t_tool *tool);
void					check_alive_cargs(t_tool *tool);
void					write_map_sti(t_tool *tool, t_carriage *carg,
														int nums, int av1);
#endif
