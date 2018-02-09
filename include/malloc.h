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
#include <string.h>
#include <pthread.h>
#include <stdlib.h>
#include <string.h>
#define ALIGN(size) (((size + sizeof(struct s_header_malloc)) + (15)) & ~(15))

pthread_mutex_t lock;

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

extern t_header_malloc *base;

void *malloc(size_t);
void free(void *);
void *realloc(void *, size_t);
void *calloc(size_t, size_t);
#endif /* !MALLOC_H_ */
