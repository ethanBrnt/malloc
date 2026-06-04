/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eburnet <eburnet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/15 14:18:40 by eburnet           #+#    #+#             */
/*   Updated: 2026/06/04 17:08:37 by eburnet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "malloc.h"

void *findPtr(void *ptr)
{
	zones_t *zone;
	
	for (size_t i = 0; i < 3; i++)
	{
		if (i == 0)
			zone = all->tiny;
		else if (i == 1)
			zone = all->small;
		else
			zone = all->large;
		while (zone)
		{
			void *start = zone->mmapStart;
			void *end = zone->mmapStart + zone->size;
			if (ptr >= start && ptr <= end)
				return (zone);
			zone = zone->next;
		}
	}
	return (NULL);
}

int is_zone_empty(zones_t *zone)
{
	header_t *head = zone->header;
	while (head)
	{
		if (head->is_free == false)
			return (0);
		head = head->next;
	}
	return (1);
}

// zones_t *findPrevZone(zones_t *actual)
// {
	
// }

void free(void *ptr)
{
	ft_printf("my free\n");
	if (ptr == NULL)
		return ;
	pthread_mutex_lock(&mutex);
	zones_t *zone = findPtr(ptr);
	ft_printf("ptr = %p\n", ptr);
	ft_printf("zone = %p\n", zone);
	if (zone == NULL)
		return (void)(pthread_mutex_unlock(&mutex));
	header_t *head = (header_t*)ptr - 1;
	ft_printf("sizeof header_t: %zu\n", sizeof(header_t));
	ft_printf("head->size: %lu\n", (unsigned long)head->size);
	ft_printf("head addr: %p\n", head);
	ft_printf("head->is_free: %d\n", head->is_free);
	ft_printf("head->size: %zu\n", head->size);
	ft_printf("head->next: %p\n", head->next);
	if (head->is_free == true)
		return (void)(pthread_mutex_unlock(&mutex));
	while (head)
	{
		ft_printf("head: %d\n", head->is_free);
		head = head->next;
	}
	head = (header_t*)ptr - 1;
	head->is_free = true;
	if (head && head->size <= all->M && is_zone_empty(zone) == 1) {
		zones_t *prev_zone = findPtr(zone - sizeof(header_t));
		prev_zone->next = zone->next;
		ft_printf("after is_zone_empty\n");
		if (munmap(zone->mmapStart, zone->size) == -1)
			return (void)(ft_printf("Error: munmap failed\n"));
	}
	else if (head && head->size > all->M) {
		if (munmap(zone->mmapStart, zone->size) == -1)
			return (void)(ft_printf("Error: munmap failed\n"));
	}
	pthread_mutex_unlock(&mutex);
}