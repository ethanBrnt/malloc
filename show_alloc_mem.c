/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   show_alloc_mem.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eburnet <eburnet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/15 15:06:06 by eburnet           #+#    #+#             */
/*   Updated: 2025/09/18 09:14:12 by eburnet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "malloc.h"

void print_zone(zones_t *actual, char *zoneName)
{
	while (actual)
	{
		ft_printf("%s: %p\n", zoneName, actual->mmapStart);
        header_t *h = actual->header;
        {
            if (!h->is_free)
            {
                size_t size = h->size;
                void *start = (char*)h + sizeof(header_t);
                void *end = (char*)start + size;
                ft_printf("%p - %p : %d bytes\n", start, end, size);
            }
            h = h->next;
        }
		actual = actual->next;
	}
}

void show_alloc_mem()
{
	if (!all)
	{
		ft_printf("No alloc\n");
		return ;
	}
	pthread_mutex_lock(&mutex);
	print_zone(all->tiny, "TINY");
	print_zone(all->small, "SMALL");
    zones_t *z = all->large;
    while (z)
	{
		ft_printf("LARGE: %p\n", z->mmapStart);
		header_t *h = z->header;
		size_t size = h->size;
		void *start = (char*)h + sizeof(header_t);
		void *end = (char*)start + size;
		ft_printf("%p - %p : %d bytes\n", start, end, size);
		z = z->next;
	}
	pthread_mutex_unlock(&mutex);
}
