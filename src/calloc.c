/*
** EPITECH PROJECT, 2018
** calloc
** File description:
** calloc
*/

#include "malloc.h"

void *calloc(size_t nmeb, size_t size)
{
	size_t total = nmeb * size;
	void *ptr = malloc(total);

	if (!total)
		return (NULL);
	ptr = memset(ptr, 0, total);
	return (ptr);
}