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

int main(void)
{
    char *p = my_malloc(100); // utilise ton malloc dans le .so
    if (!p) 
    {
        printf("NULL\n");
        return 1;
    }
    else
        printf("OK\n");

    char *p2 = my_malloc(100); // utilise ton malloc dans le .so
    if (!p2) 
    {
        printf("NULL2\n");
        return 1;
    }
    else
        printf("OK2\n");
    char *p3 = my_malloc(10000); // utilise ton malloc dans le .so
    if (!p3) 
    {
        printf("NULL3\n");
        return 1;
    }
    else
        printf("OK3\n");

  char *p4 = my_malloc(1000); // utilise ton malloc dans le .so
    if (!p4) 
    {
        printf("NULL4\n");
        return 1;
    }
    else
        printf("OK4\n");
    strcpy(p, "Salut guys");
    printf("%s\n", p);

    return 0;
}
