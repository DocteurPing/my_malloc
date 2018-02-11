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
	puts("testing malloc with tiny size and with very big size");
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

Test(myMalloc, checkData)
{
	char *s;

	s = malloc(sizeof(char) * 5);
	s = "test\n";
	cr_assert_str_eq(s, "test\n");
}

