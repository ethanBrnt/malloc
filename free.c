/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eburnet <eburnet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/15 14:18:40 by eburnet           #+#    #+#             */
/*   Updated: 2026/06/10 17:59:00 by eburnet          ###   ########.fr       */
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
		iterate = all.tiny;
	else if (actual->size <= m)
		iterate = all.small;
	else 
		iterate = all.large;
	while (iterate)
	{
		if (iterate->next == actual)
			return (iterate);
		iterate = iterate->next;
	}
	return (NULL);	
}

bool ft_is_only_zone(zones_t *zone, int type)
{
	if (type == 0 && all.tiny == zone && zone->next == NULL)
		return (true);
	else if (type == 1 && all.small == zone && zone->next == NULL)
		return (true);
	return (false);
}

void	ft_unmap(int type, zones_t *zone)
{
	if (((type == 0 || type == 1) && is_zone_empty(zone) == 1) || type == 2) {
		zones_t *prev_zone = findPrevZone(zone);
		if (prev_zone)
			prev_zone->next = zone->next;
		else
		{
			if (type == 0)
				all.tiny = zone->next;
			else if (type == 1)
				all.small = zone->next;
			else if (type == 2)
				all.large = zone->next;
		}
		if (munmap(zone->mmapStart, zone->size) == -1 || munmap(zone, sizeof(zones_t)) == -1)
			return (void)(pthread_mutex_unlock(&mutex));
	}
}

void free(void *ptr)
{
	zones_t *zone = NULL;
	zones_t *iterateZone = NULL;
	int type = -1;
	bool is_only_zone = false;

	if (ptr == NULL)
		return ;
	pthread_mutex_lock(&mutex);
	for (size_t i = 0; i < 3; i++)
	{
		if (i == 0)
			iterateZone = all.tiny;
		else if (i == 1)
			iterateZone = all.small;
		else
			iterateZone = all.large;
		while (iterateZone)
		{
			void *start = iterateZone->mmapStart;
			void *end = iterateZone->mmapStart + iterateZone->size;
			if (ptr >= start && ptr <= end)
			{
				zone = iterateZone;
				type = i;
				is_only_zone = ft_is_only_zone(zone, type);
			}
			iterateZone = iterateZone->next;
		}
	}
	if (zone == NULL)
		return (void)(pthread_mutex_unlock(&mutex));

	if (type == 0 || type == 1)
	{
		header_t *head = (header_t*)ptr - 1;
		if (head->is_free == true)
			return (void)(pthread_mutex_unlock(&mutex));
		head->is_free = true;
	}
	if (is_only_zone == false)
		ft_unmap(type, zone);
	pthread_mutex_unlock(&mutex);
}