##
## EPITECH PROJECT, 2018
## criterion
## File description:
## makefile
##

SRC	=	testsMalloc.c	\
		testsRealloc.c

OBJ	=	$(SRC:.c=.o)

NAME	=	./myTests

CFLAGS	=	-W -Wall -Werror -Wextra

LFLAGS	=	-lcriterion


all: $(NAME)

$(NAME): $(OBJ)
	gcc -o $(NAME) $(OBJ) $(CFLAGS) $(LFLAGS)

clean:
	rm -f $(OBJ)

fclean: clean
	rm -f $(NAME)

re: fclean all
