/*
** EPITECH PROJECT, 2018
** criterion
** File description:
** malloc
*/

#include <criterion/criterion.h>
#include <stdio.h>
#include <signal.h>
#include "../include/malloc.h"

void	secondTests(void)
{
	puts("testing realloc special case");
}

Test(myRealloc, firstCase, .init = secondTests)
{
	char *s;

	s = realloc(NULL, sizeof(char) * 20);
	cr_assert_neq(s, NULL);
	free(s);
}