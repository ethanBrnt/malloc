/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eburnet <eburnet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/09 11:13:11 by eburnet           #+#    #+#             */
/*   Updated: 2025/049/09 14:59:26 by eburnet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <string.h>
#include "malloc.h"
// #include <stdlib.h>

int main(void)
{
	printf("------ Show Alloc Memory ------\n");
	show_alloc_mem();
	printf("------ 10 Malloc ------\n");
	char *p[100];
	for (size_t i = 0; i < 10; i++)
	{
		if (i % 2 == 0)
			p[i] = malloc(13);
		else
			p[i] = malloc(739);
		if (!p[i]) 
			return 1;
		strcpy(p[i], "Salut guys");
		printf("malloc %ld, string: %s, adrress: %p\n", i, p[i], p[i]);
		if (i == 8)
		{
			free(p[i]);
			printf("Free 8\n");
			p[i] = NULL;
		}
	}
	show_alloc_mem();
	printf("------ Large Malloc ------\n");
	char *large = malloc(sizeof(char) * 5000);
	printf("------ Show Alloc Memory ------\n");
	show_alloc_mem();
	printf("------ Free ------\n");
	for (size_t i = 0; i < 10; i++)
	{
		printf("i: %d\n", i);
		free(p[i]);
	}
	free(large);
	printf("------ Show Alloc Memory ------\n");
	show_alloc_mem();
	return 0;
}

// TODO
// relecture du code 
// show alloc seems not to work
// make a loooot of tests

/* 
cc -g3 main.c -L. -lft_malloc -o test 
LD_LIBRARY_PATH=. ./test
*/
