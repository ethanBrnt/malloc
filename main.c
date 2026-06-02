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

int main(void)
{
	// char *p;
	// for (size_t i = 0; i < 10; i++)
	// {
	// 	if (i % 2 == 0)
	// 		p = malloc(13);
	// 	else
	// 		p = malloc(739);
	// 	if (!p) 
	// 		return 1;
	// 	strcpy(p, "Salut guys");
	// 	printf("%ld: %s\n%p\n", i, p, p);
	// 	if (i == 8)
	// 	{
	// 		free(p);
	// 		printf("Free 8\n");
	// 		p = NULL;
	// 	}
	// 	printf("\n");
	// }
	// show_alloc_mem();

	printf("------ Show Alloc Memory ------\n");
	show_alloc_mem();
	printf("------ Tiny Malloc ------\n");
	char *first = malloc(sizeof(char) * 5);
	if (!first)
		return 1;
	strcpy(first, "hey");
	printf("adress: %p\n", first);
	printf("content: %s\n", first);
	printf("------ Show Alloc Memory ------\n");
	show_alloc_mem();
	printf("------ Realloc ------\n");
	char *second =  realloc(first, 20);
	if (!second)
		return 1;
	strcpy(second, "Coucou ca vas ?");
	printf("addres: %p\n", second);
	printf("content: %s\n", second);
	printf("------ Another Tiny malloc ------\n");
	char *another = malloc(sizeof(char) * 15);
	if (!another)
		return 1;
	strcpy(another, "Hello world!");
	printf("addres: %p\n", another);
	printf("content: %s\n", another);
	printf("------ Show Alloc Memory ------\n");
	show_alloc_mem();
	printf("------ Free ------\n");
	free(second);
	free(another);
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
