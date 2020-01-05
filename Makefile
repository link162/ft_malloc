NAME		= hello
COMP		= gcc
FLAGS		= -O3 -Wall -Wextra -Werror
SRC			= main.c yurii.c
SRC_DIR		= src/
OBJ_DIR		= obj/
OBJ			= $(addprefix $(OBJ_DIR), $(SRC:.c=.o))
INC_DIR		= includes/
LIBFT_DIR	= libftprintf/
LIBFT		= $(LIBFT_DIR)libftprintf.a


all: $(NAME)

$(NAME): $(LIBFT) $(OBJ)
	@$(COMP) -o $(NAME) $(OBJ)
	@printf "\033[1;32mmalloc created \033[0m\n"

$(LIBFT):
	@make -C $(LIBFT_DIR)

$(OBJ): $(OBJ_DIR)

$(OBJ_DIR):
	@mkdir $(OBJ_DIR)

$(OBJ_DIR)%.o: $(SRC_DIR)%.c
	@$(COMP) -c $< -o $@ $(FLAGS) -I $(INC_DIR)

clean:
	@rm -rf $(OBJ)*
	@make clean -C $(LIBFT_DIR)
	@printf "\033[1;33mobject deleted \033[0m\n"

fclean: clean
	@rm -rf $(NAME)
	@make fclean -C $(LIBFT_DIR)
	@rm -rf $(OBJ_DIR)
	@printf "\033[1;31mmalloc deleted \033[0m\n"

re: fclean all

.PHONY: all clean fclean re
