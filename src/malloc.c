/*
** EPITECH PROJECT, 2018
** malloc
** File description:
** malloc.c
*/

#include "../include/malloc.h"

void *getbase()
{
	return (sbrk(0));
}

void *alloc_end(size_t size) 
{
	void *ptr = sbrk(0);
	t_header_malloc *header = ptr;
	
	if (sbrk(size) == ((void *) - 1))
		return (NULL);
	header->next = NULL;
	header->size = size - sizeof(t_header_malloc);
	header->current = ptr + sizeof(t_header_malloc);
	header->is_free = FALSE;
	return (header->current);
}

void *find_best_feed(size_t size)
{
	t_header_malloc *header = base;

	while (header->next) {
		if (header->size >= size && header->is_free)
			return (header->current);
		header = header->next;
	}
	return (alloc_end(size));
}

void *malloc(size_t size)
{
	setbuf(stdout, NULL);
	//printf("malloc: size = %ld\n", size);
	void *ptr_return;

	size = ALIGN(size);
	//pthread_mutex_lock(&lock);
	if (!base) {
		base = getbase();
		ptr_return = alloc_end(size);
		//pthread_mutex_unlock(&lock);
		return (ptr_return);
	}
	//pthread_mutex_unlock(&lock);
	ptr_return = find_best_feed(size);
	//printf("malloc: ptr = %p\n", ptr_return);
	return (ptr_return);
}

void free(void *ptr)
{
	setbuf(stdout, NULL);
	//printf("free = %p\n", ptr);
	t_header_malloc *header = base;

	if (ptr == NULL)
		return ;
	while (header->current != ptr && header->next != NULL)
		header = header->next;
	if (header->next == NULL)
		return ;
	header->is_free = TRUE;
}
void *realloc(void *ptr, size_t size)
{
	setbuf(stdout, NULL);
	//printf("malloc: size = %ld\n", size);
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
	//printf("malloc: size = %ld\n", size);
	void *ptr = malloc(size);

	ptr = memset(ptr, nmeb, size);
	return (ptr);
}