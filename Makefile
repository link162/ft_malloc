ifeq ($(HOSTTYPE),)
HOSTTYPE := $(shell uname -m)_$(shell uname -s)
endif
NAME		= libft_malloc_$(HOSTTYPE).so
TST			= dir_test/test.c
COMP		= gcc
FLAGS		= #-Wall -Wextra -Werror -O3
SRC			= malloc.c free.c realloc.c
SRC_DIR		= src/
OBJ_DIR		= obj/
OBJ			= $(addprefix $(OBJ_DIR), $(SRC:.c=.o))
INC_DIR		= includes/ 
LIBFT_DIR	= libftprintf/
LIBFT		= $(LIBFT_DIR)libftprintf.a
LINK		= libft_malloc.so


all: $(NAME) $(LINK)

$(LINK):
	@ln -s $(NAME) $(LINK)

test : all
	@$(COMP) -o test dir_test/test.c 
	@$(COMP) -o test0 dir_test/test0.c
	@$(COMP) -o test1 dir_test/test1.c
	@$(COMP) -o test2 dir_test/test2.c
	@$(COMP) -o test3 dir_test/test3.c
	@$(COMP) -o test3a dir_test/test3a.c
	@$(COMP) -o test4 dir_test/test4.c 
	@$(COMP) -o test5 dir_test/test5.c -L. -lft_malloc -I $(INC_DIR) -I $(LIBFT_DIR)
	@printf "\033[1;32mtest files created \033[0m\n"

$(NAME): $(LIBFT) $(OBJ)
	@$(COMP) -o $(NAME) $(OBJ) -shared $(LIBFT)
	@printf "\033[1;32m$(NAME) created \033[0m\n"

$(LIBFT):
	@make -C $(LIBFT_DIR)

$(OBJ): $(OBJ_DIR)

$(OBJ_DIR):
	@mkdir $(OBJ_DIR)

$(OBJ_DIR)%.o: $(SRC_DIR)%.c
	@$(COMP) -c $< -fPIC -o $@ $(FLAGS) -I $(INC_DIR) -I $(LIBFT_DIR)

clean:
	@rm -rf $(OBJ)* $(EXE) *.o test* $(LINK)
	@make clean -C $(LIBFT_DIR)
	@printf "\033[1;33mobject deleted \033[0m\n"

fclean: clean
	@rm -rf $(NAME) $(OBJ_DIR)
	@make fclean -C $(LIBFT_DIR)
	@printf "\033[1;31m$(NAME) deleted \033[0m\n"

re: fclean all

link:
	@$(CURR) = pwd -P
	@echo $(CURR)

.PHONY: all clean fclean re
