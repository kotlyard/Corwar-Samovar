NAME = libft.a

CFLAGS += -Wall -Wextra -Werror

FILES = ft_printf.c \
        tools_printf.c \
        handle_num.c \
        tools_parse.c \
        width_and_acc.c \
        float.c \
        handle_wchar.c \
        fucked_up_cases.c

LIBFILES =  ft_strlen.c \
            ft_strdup.c \
            ft_strnew.c \
            ft_strchr.c \
            ft_strsub.c \
            ft_strjoin.c \
            ft_strstr.c \
            ft_atoi.c \
            ft_isdigit.c \
            ft_itoa.c \
            ft_strdel.c \
            ft_strcpy.c \
            ft_strequ.c \
            ft_memdel.c \
            ft_strclr.c \
			ft_memset.c \
			ft_bzero.c \
			ft_memcpy.c \
			ft_memmove.c \
			ft_memchr.c \
			ft_memcmp.c \
			ft_strncpy.c \
			ft_strcat.c \
			ft_strncat.c \
			ft_strlcat.c \
			ft_strrchr.c \
			ft_strnstr.c \
			ft_strncmp.c \
			ft_strcmp.c \
			ft_isalpha.c \
			ft_isalnum.c \
			ft_isascii.c \
			ft_isprint.c \
			ft_toupper.c \
			ft_tolower.c \
			ft_memalloc.c \
			ft_striter.c \
			ft_striteri.c \
			ft_strmap.c \
			ft_strmapi.c \
			ft_strtrim.c \
			ft_strsplit.c \
			ft_putchar.c \
			ft_putstr.c \
			ft_putendl.c \
			ft_putnbr.c \
			ft_putchar_fd.c \
			ft_putstr_fd.c \
			ft_putendl_fd.c \
			ft_putnbr_fd.c \
			ft_lstnew.c \
			ft_lstdelone.c \
			ft_lstdel.c \
			ft_lstadd.c \
			ft_lstiter.c \
			ft_lstmap.c \
			ft_strnequ.c \
			get_next_line.c

.PHONY = all clean fclean clean re

PRINTFSRCS  = $(addprefix src/ft_printf/, $(FILES))
LIBSRCS = $(addprefix src/, $(LIBFILES))


OBJ = $(PRINTFSRCS:.c=.o)
LIBOBJ = $(LIBSRCS:.c=.o)

all: $(NAME)

$(OBJ): %.o: %.c
	@gcc -c $(CFLAGS) -I inc $< -o $@

$(LIBOBJ): %.o: %.c
	@gcc -c $(CFLAGS) -I inc $< -o $@

$(NAME): $(LIBOBJ) $(OBJ)
	@ar rcs $(NAME) $(OBJ) $(LIBOBJ)
	@echo "\033[32mlibft library is ready to use.\033[0m"

clean:
	@rm -rf $(OBJ) $(LIBOBJ)
	@echo "\033[31mlibft Object Files have been removed\033[0m"

fclean: clean
	@rm -rf $(NAME)
	@echo "\033[31mlibft library has been removed\033[0m"

re: fclean all