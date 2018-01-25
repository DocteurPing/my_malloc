##
## EPITECH PROJECT, 2018
## Malloc
## File description:
## Makefile
##

SRC	=	src/malloc.c	\

OBJ	=	$(SRC:.c=.o)

MODE	=	normal

CFLAGS	=	-W -Wall -Wextra -Iinclude

NAME	=	libmy_malloc.so

all: $(NAME)

$(NAME):
	gcc $(CFLAGS) -shared -fpic $(SRC) -o $(NAME)

clean:
	rm -rf $(OBJ)

fclean:	clean
	rm -rf $(NAME)

re: fclean all
