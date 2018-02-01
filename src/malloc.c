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
	printf("alloc_end\n");
	if (sbrk(size) == ((void *) - 1))
		return (NULL);
	header->next = NULL;
	header->size = size - sizeof(t_header_malloc);
	header->current = ptr + sizeof(t_header_malloc);
	header->is_free = FALSE;
	/* if (tmp->next == NULL)
		tmp->next = header;
	else {
		for (; tmp->next != NULL; tmp = tmp->next)
			printf("test\n");
	}
	*tmp->next = *header; */
	return (header->current);
}

void *find_best_feed(size_t size)
{
	t_header_malloc *header = base;

	setbuf(stdout, NULL);
	printf("find_best_feed\n");
	while (header->next != NULL) {
		if (header->size > size && header->is_free)
			return (header->current);
		header = header->next;
		//printf("test fbf\n");
	}
	return (alloc_end(size));
}

void *my_malloc(size_t size)
{
	setbuf(stdout, NULL);
	printf("malloc: size = %ld\n", size);
	void *ptr_return;

	size = ALIGN(size);
	//pthread_mutex_lock(&lock);
	if (!base) {
		base = getbase();
		ptr_return = alloc_end(size);
		//pthread_mutex_unlock(&lock);
		printf("malloc without base: ptr = %p\n", ptr_return);
		return (ptr_return);
	}
	//pthread_mutex_unlock(&lock);
	ptr_return = find_best_feed(size);
	printf("malloc with base: ptr = %p\n", ptr_return);
	return (ptr_return);
}

void my_free(void *ptr)
{
	setbuf(stdout, NULL);
	t_header_malloc *header = base;
	printf("free: %p\n", ptr);
	if (ptr == NULL)
		return ;
	while (header->current != ptr && header->next != NULL) {
		header = header->next;
	}
		printf("free %p\n", header);
	if (header->next == NULL)
		return ;
	printf("free = %p\tsize = %d\n", ptr, header->size);
	header->is_free = TRUE;
}
void *my_realloc(void *ptr, size_t size)
{
	setbuf(stdout, NULL);
	printf("realloc: size = %ld\n", size);
	void *new_ptr = my_malloc(size);

	if (size == 0) {
		my_free(ptr);
		return (NULL);
	}
	if (ptr) {
		new_ptr = memcpy(new_ptr, ptr, size);
		my_free(ptr);
	}
	return (new_ptr);
}

void *my_calloc(size_t nmeb, size_t size)
{
	setbuf(stdout, NULL);
	printf("calloc: size = %ld\n", size);
	void *ptr = my_malloc(size);

	ptr = memset(ptr, nmeb, size);
	return (ptr);
}