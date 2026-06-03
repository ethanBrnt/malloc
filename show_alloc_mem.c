/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   show_alloc_mem.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eburnet <eburnet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/15 15:06:06 by eburnet           #+#    #+#             */
/*   Updated: 2026/06/03 15:44:33 by eburnet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "malloc.h"

void print_zone(zones_t *actual, char *zoneName)
{
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
			}
			header = header->next;
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
	zones_t *largeZone = all->large;
	while (largeZone) {
		ft_printf("LARGE: %p\n", largeZone->mmapStart);
		size_t size = largeZone->size; // pas init
		ft_printf("HERE\n");
		void *start = (char *)sizeof(zones_t);
		void *end = (char *)start + size;
		ft_printf("%p - %p : %d bytes\n", start, end, size);
		largeZone = largeZone->next;
	}
	pthread_mutex_unlock(&mutex);
}
