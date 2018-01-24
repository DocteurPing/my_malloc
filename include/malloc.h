/*
** EPITECH PROJECT, 2018
** malloc
** File description:
** malloc.h
*/

#ifndef MALLOC_H_
	#define MALLOC_H_

#include <unistd.h>
#include <stdio.h>
#include <assert.h>

void *base = NULL;

enum e_bool {
	FALSE,
	TRUE
};

typedef struct	s_header_malloc {
	struct s_header_malloc *next;
	void *current;
	unsigned int size;
	enum e_bool is_free;
} t_header_malloc;

#endif /* !MALLOC_H_ */
