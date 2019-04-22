NAME = asm

C = gcc

CFLAG = -Wall -Wextra -Werror

INC = -I ./inc

LIBDIR = libft

LIBFT = $(LIBDIR)/libft.a

SRCDIR = src

SRC = 	b_tokenize.c \
		get_header.c \
		input.c \
		list_tools.c  \
		main.c \
		output.c \
		tokenize.c \
		tools.c \
		tools_b_tokenize.c \
		header_tools.c \
		err_manage.c \
		check_args.c \
		bonus_flag.c \
		norm_isfucked_up.c \
		additional_funcs.c 


OBJ = $(SRC:.c=.o)

.PHONY: all clean fclean

.NOTPARALLEL: all clean fclean

%.o: $(SRCDIR)/%.c
	@$(C) $(CFLAG) -c $< $(INC)

all: $(NAME)

$(NAME): $(OBJ)
	@$(C) $(CFLAG) -o $(NAME) $(OBJ) ../libft/libft.a
	@echo "\033[32mAsm is ready to use.\033[0m"

clean:
	@/bin/rm -rf  *.o
	@echo "\033[31mObject files have been removed.\033[m"

fclean: clean
	@/bin/rm -f $(NAME)
	@echo "\033[31mAsm has been removed.\033[0m"

re: fclean all
