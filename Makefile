.PHONY: all clean fclean

.NOTPARALLEL: all clean fclean


all: 
	@make -C libft/
	@make -C asm/
	@make -C vm/
	@echo "Done."

clean:
	@make clean -C  libft/
	@make clean -C  asm/
	@make clean -C  vm/

fclean:
	@make fclean -C  libft/
	@make fclean -C  asm/
	@make fclean -C  vm/

re: fclean all
