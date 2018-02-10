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

void	firstTests(void)
{
	puts("firstTests: testing malloc with tiny size and with very big size");
}

Test(myMalloc, tinyMalloc, .init = firstTests)
{
	char *s;
 
	s = malloc(sizeof(char) * 1);
	cr_assert_neq(s, NULL);
	free(s);
}

Test(myMalloc, bigMalloc)
{
	char *s;

	s = malloc(sizeof(char) * 5 * 1024 * 1024);
	cr_assert_neq(s, NULL);
	free(s);
}

