/*
** EPITECH PROJECT, 2018
** realloc
** File description:
** realloc
*/

#include "malloc.h"

void *realloc(void *ptr, size_t size)
{
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