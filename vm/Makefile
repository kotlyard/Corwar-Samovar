# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: vzomber <marvin@42.fr>                     +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2018/11/09 17:07:09 by vzomber           #+#    #+#              #
#    Updated: 2018/12/27 17:57:01 by dkotlyar         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = corewar

SRC_COR =	vm/algorithm.c vm/carriage.c vm/exe_aff.c vm/exe_fork.c \
			vm/exe_ldi.c vm/exe_live.c vm/exe_lldi.c vm/exe_st.c vm/exe_sub.c \
			vm/exe_zjmp.c vm/add_player.c vm/args.c vm/errors.c vm/exe_add.c \
			vm/exe_and.c vm/exe_ld.c vm/exe_lfork.c vm/exe_lld.c vm/exe_or.c \
			vm/exe_sti.c vm/exe_xor.c vm/main.c vm/screen.c vm/screen2.c \
			vm/verbosity.c vm/useful.c vm/write_map.c

OBJ_COR = $(SRC_COR:.c=.o)

FLAGS = -Wall -Wextra -Werror

all: $(NAME)

$(NAME): $(OBJ_COR)
	@gcc $(FLAGS) $(OBJ_COR) -l ncurses -L ../libft/ -lft -o $(NAME)
	@echo "\033[32m\033[36m  corewar \033[32mis ready\033[0m"

%.o: %.c inc/vm.h
	@gcc -c $< -o $@ $(FLAGS) -I inc/ -I ../libft/inc

clean:
	@rm -f $(OBJ_COR)
	@echo "vm object files removed"

fclean: clean 
	@rm -f $(NAME)
	@echo "vm executable removed"

re: fclean all
