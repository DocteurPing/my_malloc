##
## EPITECH PROJECT, 2018
## Malloc
## File description:
## Makefile
##

SRC	=	src/malloc.c

OBJ	=	$(SRC:.c=.o)

CFLAGS  =       -W -Wall -Wextra -Werror -Iinclude

NAME	=	libmy_malloc.so

all: $(NAME)

$(NAME):	$(OBJ)
	gcc -shared -o $(NAME) -fpic $(SRC)

clean:
	rm -rf $(OBJ)

fclean:	clean
	rm -rf $(NAME)

re:
	fclean all
