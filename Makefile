NAME = hello

COMP = gcc
FLAGS = -g3
FILES = main.c yurii.c
SRC_DIR = src/
SRC = $(addprefix $(SRC_DIR), $(FILES))
OBJ_DIR = obj/
OBJ = $(addprefix , $(FILES:.c=.o))
INC_DIR = includes/


all: $(NAME)

$(NAME): $(OBJ)
	$(COMP) $(FLAGS) -o $(NAME) $(OBJ)

$(OBJ): $(OBJ_DIR) $(SRC)

$(OBJ_DIR):
	mkdir $(OBJ_DIR)
$(OBJ):
	$(COMP) $(FLAGS) -c $(SRC) -I $(INC_DIR)

clean:
	rm -rf *.dSYM $(NAME) $(OBJ_DIR) *.o

