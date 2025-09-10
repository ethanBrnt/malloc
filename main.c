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
    for (size_t i = 0; i < 120; i++)
    {
        char *p = my_malloc(100); // utilise ton malloc dans le .so
        if (!p) 
            return 1;
        strcpy(p, "Salut guys");
        printf("%ld: %s\n", i, p);
    }
    
   

    return 0;
}
