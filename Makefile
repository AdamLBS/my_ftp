##
## EPITECH PROJECT, 2021
## makefile
## File description:
## makefile
##

NAME = myftp

SRC = *.c

all:
	gcc -g3 -o $(NAME) $(SRC) -L./include -I./include

clean:
	rm -f *~ | rm -f *.o

fclean: clean
	rm -f $(NAME)

re:	fclean all