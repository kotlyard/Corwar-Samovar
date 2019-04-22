/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   asm.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dkotlyar <dkotlyar@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/27 15:44:32 by dkotlyar          #+#    #+#             */
/*   Updated: 2018/12/27 17:29:26 by dkotlyar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ASM_ASM_H
# define ASM_ASM_H

/*
**   INCLUDES
*/

# include "libft.h"
# include "get_next_line.h"
# include <fcntl.h>
# include "op.h"

/*
**   MACROS
*/

# define CLR_RED "\x1b[31m"
# define CLR_GRN "\x1b[32m"
# define CLR_YEL "\x1b[33m"
# define CLR_BLU "\x1b[34m"
# define CLR_MAG "\x1b[35m"
# define CLR_CYA "\x1b[36m"
# define CLR_RST "\x1b[0m"
# define CURR_LINE data->lines_without_meta[i]

/*
**   STRUCTURES
*/

typedef struct			s_token
{
	char				**labels;
	uint8_t				op_id;
	char				**args;
	struct s_token		*next;

}						t_token;

typedef struct			s_arg
{
	char				arg_type;
	uint32_t			value;
	char				*reference;
}						t_arg;

typedef struct			s_b_token
{
	uint8_t				op_code;
	char				dir_size;
	uint8_t				arg_code;
	uint8_t				arg_num;
	t_arg				args_value[3];
	char				**labels;
	uint32_t			bytelen;
	uint32_t			bytepos;
	struct s_b_token	*next;
}						t_b_token;

typedef struct			s_string
{
	char				*line;
	struct s_string		*next;

}						t_string;

typedef struct			s_op
{
	char				*op_name;
	int					arg_num;
	unsigned			arg_type[3];
	char				op_id;
	char				arg_type_is_need;
	char				dir_size;
}						t_op;

typedef struct			s_asm
{
	char				**lines;
	size_t				lines_to_skip;
	uint32_t			file_len;
	char				**lines_without_meta;
	char				*name;
	char				*comment;
	t_header			header;
	t_op				*op_tab;
	t_string			*label_list;
	t_token				*tokens;
	t_b_token			*b_tokens;
	char				*file_name;
	uint32_t			ref_to_last;
	uint8_t				flag;
}						t_asm;

extern t_op	g_tab[17];

/*
**   **************** FUNCTIONS PROTOTYPES *****************
*/

/*
**   _________________MAIN.C__________________
*/

char					is_label(char const *str);

/*
**   _________________TOOLS.C__________________
*/

void					print_error(char *msg, ssize_t line_number);
ssize_t					init_all_and_check_basic_errors(t_asm *data,
int ac, char **av);
int						is_in_here(char symb, char *where);
void					print_tokens(t_token *op_list, t_op *op);
t_string				*cut_labels(t_string *list, int *len);
char					**clean_str_arr_from_trash(char **lines, size_t start);
char					**read_file_and_return_strarr(ssize_t fd, t_asm *data);
t_string				*clean_from_comment(t_string *list);
void					add_to_list(char *line, t_string **list, char to_trim);
char					**from_list_to_strarr(t_string *list, int len);
void					free_list(t_string *list);
size_t					get_header(t_asm *data);
size_t					save_without_nl(char is_comment, t_asm *data,
char *start);
size_t					save_with_nl(char is_comment, t_asm *data,
char const *start, size_t i);
unsigned				pass_whitespaces(char *str, char const *what);

void					tokenize_commands(t_asm *data);

/*
**   _________________B-TOKENIZE.C__________________
*/

t_b_token				*b_tokenize(t_asm *data);

/*
**   _________________TOOLS_B-TOKENIZE.C__________________
*/

uint8_t					get_arg_size(char c);
void					set_references(t_b_token *head, t_asm *data);
void					print_b_tokens(t_b_token *b_token);
uint32_t				count_chars(char const *str, char c);

/*
**   _________________OUTPUT.C__________________
*/

char					*get_output_file_name(char *str);
void					create_file(t_asm *data);
uint16_t				swap_uint16(uint16_t val);
uint32_t				swap_uint32(uint32_t val);

/*
**   _________________ERR_MANAGE.C__________________
*/

void					err_manage(t_token *op_list);

/*
**   _________________CHECK_ARGS.C__________________
*/

int						check_dir(char *args, char *instr, int num);
int						check_ind(char *args, char *instr, int num);
int						check_reg(char *args, char *instr, int num);

void					flag_processing(t_asm *data);
int						ch_fuck(char *str);
char					*mk_magic(char *str, char *const op_name);
int						thanks_norm(char **s1, char **s2);
void					print_labels(t_b_token *tokens);
void					print_byte_values(uint8_t size, uint32_t value);
int						is_line_a_label(char *line);

#endif
