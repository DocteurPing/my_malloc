/*
** EPITECH PROJECT, 2018
** malloc
** File description:
** malloc.c
*/

#include "../include/malloc.h"

void *get_base()
{
	return (sbrk(0));
}

void *alloc_end(size_t size) 
{
	void *ptr = sbrk(0);
	void *ptr_next = sbrk(size);
	t_header_malloc *header = ptr;
	
	(void)ptr_next;
	header->next = NULL;
	header->size = size - sizeof(t_header_malloc);
	header->current = header + sizeof(t_header_malloc);
	header->is_free = FALSE;
	return (header->current);
}

void *find_best_feed(void *base, size_t size)
{
	t_header_malloc *header = base;

	while (header->next) {
		if (header->size > size && header->is_free)
			return (header->current);
		header = header->next;
	}
	return (alloc_end(size));
}

void *malloc(size_t size)
{
	void *ptr_return;

	printf("Malloc: starting\n");
	if (!base) {
		base = get_base();
		ptr_return = alloc_end(size + sizeof(t_header_malloc));
		base = ptr_return;
		return (ptr_return);
	}
	return (find_best_feed(base, size + sizeof(t_header_malloc)));
}

void free(void *ptr)
{
	t_header_malloc *header = base;

	while (header->current != ptr)
		header = header->next;
	header->is_free = TRUE;
}