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

void	thirdTests(void)
{
	puts("calling calloc()");
}

Test(myCalloc, callocCall, .init = thirdTests)
{
	char *s;

	s = calloc(20, sizeof(char));
	cr_assert_neq(s, NULL);
	free(s);
}
