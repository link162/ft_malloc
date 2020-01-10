ifeq ($(HOSTTYPE),)
HOSTTYPE := $(shell uname -m)_$(shell uname -s)
endif
HOSTTYPE	:= $(HOSTTYPE)
NAME		= libft_malloc_$(HOSTTYPE).so
EXE			= exec
TST			= test
COMP		= gcc
FLAGS		= -O3 -Wall -Wextra -Werror
SRC			= malloc.c
SRC_DIR		= src/
OBJ_DIR		= obj/
OBJ			= $(addprefix $(OBJ_DIR), $(SRC:.c=.o))
INC_DIR		= includes/ 
LIBFT_DIR	= libftprintf/
LIBFT		= $(LIBFT_DIR)libftprintf.a


all: $(NAME)

file: $(EXE)

TST2: $(TST)

$(TST) : $(NAME)
	@$(COMP) -o $(TST) test.c -L. -lft_malloc_$(HOSTTYPE) -I $(INC_DIR)
	@printf "\033[1;32m$(TST) created \033[0m\n"

$(EXE) : $(LIBFT) $(OBJ) src/main.c
	@$(COMP) -c src/main.c -I $(INC_DIR) -I $(LIBFT_DIR)
	@$(COMP) -o $(EXE) main.o $(OBJ) $(LIBFT)
	@printf "\033[1;32m$(EXE) created \033[0m\n"

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
	@rm -rf $(OBJ)* $(EXE) *.o a.out $(TST)
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

.PHONY: all clean fclean re file
