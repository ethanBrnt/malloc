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
	
	char *first = malloc(sizeof(char) * 5);
	if (!first)
	    return 1;
	strcpy(first, "hey");
	printf("%p\n", first);
	printf("%s\n", first);
	printf("------------\n");
	char *second =  realloc(first, 20);
	strcpy(second, "Coucou ca vas ?");
	printf("%p\n", second);
	printf("%s\n", second);
	show_alloc_mem();

	return 0;
}
