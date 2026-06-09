/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eburnet <eburnet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/15 14:18:40 by eburnet           #+#    #+#             */
/*   Updated: 2026/06/09 09:23:03 by eburnet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "malloc.h"

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

zones_t *findPrevZone(zones_t *actual)
{
	zones_t *iterate;
	if (actual->size <= n)
		iterate = all->tiny;
	else if (actual->size <= m)
		iterate = all->small;
	else 
		iterate = all->large;
	while (iterate)
	{
		if (iterate->next == actual)
			return (iterate);
		iterate = iterate->next;
	}
	return (NULL);	
}

void free(void *ptr)
{
	zones_t *zone = NULL;
	zones_t *iterateZone = NULL;
	int type = -1;

	// ft_printf("my free\n");
	if (ptr == NULL)
		return ;
	pthread_mutex_lock(&mutex);
	for (size_t i = 0; i < 3; i++)
	{
		if (i == 0)
			iterateZone = all->tiny;
		else if (i == 1)
			iterateZone = all->small;
		else
			iterateZone = all->large;
		while (iterateZone)
		{
			void *start = iterateZone->mmapStart;
			void *end = iterateZone->mmapStart + iterateZone->size;
			if (ptr >= start && ptr <= end)
			{
				zone = iterateZone;
				type = i;
			}
			iterateZone = iterateZone->next;
		}
	}
	if (zone == NULL)
		return (void)(pthread_mutex_unlock(&mutex));

	header_t *head = (header_t*)ptr - 1;
	if (head->is_free == true)
		return (void)(pthread_mutex_unlock(&mutex));
	head->is_free = true;
	// ft_printf("all tiny: %p, small: %p\n", all->tiny, all->small);
	if (((type == 0 || type == 1) && is_zone_empty(zone) == 1) || type == 2) {
		// ft_printf("in the free ZONE zone->size %d, m %d head->size %d\n", zone->size, m, head->size);
		zones_t *prev_zone = findPrevZone(zone);
		if (prev_zone)
			prev_zone->next = zone->next;
		else
		{
			if (type == 0)
				all->tiny = zone->next;
			else if (type == 1)
				all->small = zone->next;
			else if (type == 2)
				all->large = zone->next;
		}
		if (munmap(zone->mmapStart, zone->size) == -1 || munmap(zone, sizeof(zones_t)) == -1)
			return (void)(ft_putstr_fd("Error: munmap failed\n", 2));
	}
	pthread_mutex_unlock(&mutex);
}