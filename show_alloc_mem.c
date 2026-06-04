/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   show_alloc_mem.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eburnet <eburnet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/15 15:06:06 by eburnet           #+#    #+#             */
/*   Updated: 2026/06/04 16:26:59 by eburnet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "malloc.h"

int print_zone(zones_t *actual, char *zoneName)
{
	int total = 0;
	while (actual)
	{
		ft_printf("%s: %p\n", zoneName, actual->mmapStart);
		header_t *header = actual->header;
		while (header) {
			if (header->is_free == false) {
				size_t size = header->size;
				void *start = (char*)header + sizeof(header_t);
				void *end = (char*)start + size;
				ft_printf("%p - %p : %d bytes\n", start, end, size);
				total = total + size;
			}
			header = header->next;
		}
		actual = actual->next;
	}
	return (total);
}

void show_alloc_mem()
{
	int total = 0;
	if (!all)
	{
		ft_printf("No alloc\n");
		return ;
	}
	pthread_mutex_lock(&mutex);
	total = total + print_zone(all->tiny, "TINY");
	total = total + print_zone(all->small, "SMALL");
	zones_t *largeZone = all->large;
	while (largeZone) {
		ft_printf("LARGE: %p\n", largeZone->mmapStart);
		size_t size = largeZone->size; // pas init
		ft_printf("HERE\n");
		void *start = (char *)sizeof(zones_t);
		void *end = (char *)start + size;
		ft_printf("%p - %p : %d bytes\n", start, end, size);
		total = total + size;
		largeZone = largeZone->next;
	}
	ft_printf("Total : %d bytes\n", total);
	pthread_mutex_unlock(&mutex);
}
