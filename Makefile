NAME = hello

COMP = gcc
FLAGS = -g3
SRC = main.c


all:
	$(COMP) $(FLAGS) $(SRC) -o $(NAME)

