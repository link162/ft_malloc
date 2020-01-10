NAME		=	libftprintf.a

LIB			=	libft/
LIB_N		=	libft.a

SRC_D		=	src/
SRC			=	ft_printf.c \
				parsing.c \
				parsing2.c \
				print_int.c \
				prepare_to_print.c \
				print_char_str.c \
				print_hex.c \
				print_double.c \
				print_octal.c \

OBJ_D		=	obj/
OBJ			=	$(addprefix $(OBJ_D), $(SRC:.c=.o))

INCLUDE		=	-I includes/
CFLAGS		=	-O3 -Wall -Wextra -Werror
C			=	gcc

all: $(NAME)

$(NAME): $(OBJ)
	@make -C $(LIB)
	@cp $(LIB)$(LIB_N) $(NAME)
	@ar -r $(NAME) $(OBJ)
	@ranlib $(NAME)
	@printf "\033[1;32mlibftprintf created \033[0m\n"

$(OBJ): | $(OBJ_D)

$(OBJ_D):
	@mkdir -p $(OBJ_D)$(SRC_D)

$(OBJ_D)%.o:$(SRC_D)%.c
	@$(C) $(CFLAGS) $(INCLUDE) -o $@ -c $<

clean:
	@make clean -C libft
	@rm -f $(OBJ)

fclean: clean
	@make fclean -C libft
	@rm -f $(NAME)
	@rm -rf $(OBJ_D)
	@printf "\033[1;31mlibftprintf deleted \033[0m\n"

re: fclean all

.PHONY: all clean fclean re
