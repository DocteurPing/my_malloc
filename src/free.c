/*
** EPITECH PROJECT, 2018
** free
** File description:
** free
*/

#include "malloc.h"

void free(void *ptr)
{
	t_header_malloc *header;

	if (ptr == NULL)
		return ;
	header = ptr - sizeof(t_header_malloc);
	header->is_free = TRUE;
}