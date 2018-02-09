/*
** EPITECH PROJECT, 2018
** malloc
** File description:
** malloc.c
*/

#include "../include/malloc.h"

t_header_malloc *base = NULL;
pthread_mutex_t lock = PTHREAD_MUTEX_INITIALIZER;

void *getbase()
{
	return (sbrk(0));
}

void *alloc_end(size_t size)
{
	void *ptr = sbrk(0);
	t_header_malloc *header = ptr;
	t_header_malloc *tmp = base;

	setbuf(stdout, NULL);
	if (sbrk(size) == ((void *) - 1)) {
		exit(0);
		return (NULL);
	}
	header->next = NULL;
	header->size = size - sizeof(t_header_malloc);
	header->current = (char *)ptr + sizeof(t_header_malloc);
	header->is_free = FALSE;
	for (; tmp->next != NULL; tmp = tmp->next);
	tmp->next = header;
	return (header->current);
}

void *find_best_feed(size_t size)
{
	t_header_malloc *header = base;

	setbuf(stdout, NULL);
	if (header == NULL)
		return (NULL);
	while (header->next != NULL) {
		if (header->is_free == TRUE && header->size >= size) {
			header->is_free = FALSE;
			pthread_mutex_unlock(&lock);
			return (header->current);
		}
		header = header->next;
	}
	pthread_mutex_unlock(&lock);
	return (alloc_end(size));
}

void *setup_alloc(size_t size)
{
	t_header_malloc *header = base;
	void *p = NULL;
	
	setbuf(stdout, NULL);
	if ((p = sbrk(size)) == ((void *) - 1)) {
		pthread_mutex_unlock(&lock);
		exit(0);
	}
	header->next = NULL;
	header->size = size - sizeof(t_header_malloc);
	header->current = (char *)base + sizeof(t_header_malloc);
	header->is_free = FALSE;
	pthread_mutex_unlock(&lock);
	return (header->current);
}

void *malloc(size_t size)
{
	setbuf(stdout, NULL);
	void *ptr_return;

	size = ALIGN(size);
	if (size == 0)
		return (NULL);
	pthread_mutex_lock(&lock);
	if (!base) {
		base = sbrk(0);
		ptr_return = setup_alloc(size);
		return (ptr_return);
	}
	ptr_return = find_best_feed(size);
	return (ptr_return);
}

void free(void *ptr)
{
	setbuf(stdout, NULL);
	t_header_malloc *header;

	if (ptr == NULL)
		return ;
	header = ptr - sizeof(t_header_malloc);
	header->is_free = TRUE;
}
void *realloc(void *ptr, size_t size)
{
	setbuf(stdout, NULL);
	void *new_ptr = malloc(size);

	if (size == 0) {
		free(ptr);
		return (NULL);
	}
	if (ptr) {
		new_ptr = memcpy(new_ptr, ptr, size);
		free(ptr);
	}
	return (new_ptr);
}

void *calloc(size_t nmeb, size_t size)
{
	setbuf(stdout, NULL);
	void *ptr = malloc(size);

	ptr = memset(ptr, nmeb, size);
	return (ptr);
}