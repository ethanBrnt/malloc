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

#include "malloc.h"
#include <stdio.h>
#include <string.h>

/* 
    TODO
    test malloc null
    test bcp de malloc
    test malloc BIIIIG size

    test free null
    test free invalid pointer
*/

int main(void)
{
    char *p;
    for (size_t i = 0; i < 101; i++)
    {
        p = my_malloc(512);
        if (!p) 
            return 1;
        strcpy(p, "Salut guys");
        printf("%ld: %s\n", i, p);
        printf("%p\n", p);
        if (i == 98)
        {
            my_free(p);
            printf("Free 98\n");
            p = NULL;
        }
        printf("\n");
    }
    
    // char *first = my_malloc(10);
    // printf("------------\n");
    // char *second =  my_malloc(20);
    
    // printf("%p\n", first);
    // printf("%p\n", second);

    return 0;
}
