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
	printf("break pos : %p\n", getbase());	
	//printf("alloc_end\n");
	printf("appel de sbrk avec la taille %ld\n", size);
	if (sbrk(size) == ((void *) - 1)) {
		printf("lel sbrk a planté :)\n");
		exit(0);
		return (NULL);
	}
	header->next = NULL;
	header->size = size - sizeof(t_header_malloc);
	header->current = (char *)ptr + sizeof(t_header_malloc);
	header->is_free = FALSE;
	for (; tmp->next != NULL; tmp = tmp->next);
	tmp->next = header;
	printf("next = %p\n", tmp->next);
	return (header->current);
}

void *find_best_feed(size_t size)
{
	t_header_malloc *header = base;

	setbuf(stdout, NULL);
	printf("find_best_feed %p-%p : %p\n", header, header->next, sbrk(0));
	if (header == NULL)
		return (NULL);
	while (header->next != NULL) {
		//printf("searching...\n");
		if (header->is_free == TRUE && header->size >= size) {
			//printf("find a free block\n");
			header->is_free = FALSE;
			return (header->current);
		}
		header = header->next;
	}
	printf("No free block available\n");
	return (alloc_end(size));
}

void *setup_alloc(size_t size)
{
	t_header_malloc *header = base;
	void *p = NULL;
	
	setbuf(stdout, NULL);
	printf("alloc_end\n");
	if ((p = sbrk(size)) == ((void *) - 1)) {
		printf("lel sbrk a planté :)\n");
		exit(0);
	}
	printf("nouveau break (size: %ld): %p\n", size, p);
	header->next = NULL;
	header->size = size - sizeof(t_header_malloc);
	header->current = (char *)base + sizeof(t_header_malloc);
	header->is_free = FALSE;
	return (header->current);
}

void *malloc(size_t size)
{
	setbuf(stdout, NULL);
	printf("malloc: size = %ld\n", size);
	void *ptr_return;

	size = ALIGN(size);
	if (size == 0)
		return (NULL);
	//pthread_mutex_lock(&lock);
	if (!base) {
		printf("appel de setupalloc\n");
		base = sbrk(0);
		ptr_return = setup_alloc(size);
		//pthread_mutex_unlock(&lock);
		//printf("malloc without base: ptr = %p\n", ptr_return);
		return (ptr_return);
	}
	//pthread_mutex_unlock(&lock);
	ptr_return = find_best_feed(size);
	printf("malloc with base: ptr = %p\n", ptr_return);
	return (ptr_return);
}

void free(void *ptr)
{
	setbuf(stdout, NULL);
	t_header_malloc *header;
;
	printf("free: %p\n", ptr);
	if (ptr == NULL)
		return ;
	header = ptr - sizeof(t_header_malloc);
 	/* while (header->next != NULL && header->current != ptr)
		header = header->next;
	if (header->next == NULL && header->current != ptr) {
		printf("free not found\n");
		return ;
	} */
	
	header->is_free = TRUE;
	//if (header->next == NULL)
		//sbrk(-header->size);
	printf("free = %p\tsize = %d\n", ptr, header->size);
}
void *realloc(void *ptr, size_t size)
{
	setbuf(stdout, NULL);
	printf("realloc: size = %ld\n", size);
	void *new_ptr = malloc(size);
	//size_t size_to_copy;
	//t_header_malloc *header;

	if (size == 0) {
		free(ptr);
		return (NULL);
	}
	if (ptr) {
		//header = ptr - sizeof(t_header_malloc);
		//size_to_copy = header->size;
		new_ptr = memcpy(new_ptr, ptr, size);
		free(ptr);
	}
	return (new_ptr);
}

void *calloc(size_t nmeb, size_t size)
{
	setbuf(stdout, NULL);
	printf("calloc: size = %ld\n", size);
	void *ptr = malloc(size);

	ptr = memset(ptr, nmeb, size);
	return (ptr);
}