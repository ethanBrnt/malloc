/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eburnet <eburnet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/15 14:18:40 by eburnet           #+#    #+#             */
/*   Updated: 2026/06/03 15:09:33 by eburnet          ###   ########.fr       */
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

void free(void *ptr)
{
	ft_printf("my free\n");
	if (ptr == NULL)
		return ;
	pthread_mutex_lock(&mutex);
	zones_t *zone = findPtr(ptr);
	if (zone == NULL)
		return (void)(pthread_mutex_unlock(&mutex));
	header_t *head = (header_t*)ptr - 1;
	if (head->is_free == true)
		return (void)(pthread_mutex_unlock(&mutex));
	head->is_free = true;
	if (head && head->size <= all->M && is_zone_empty(zone) == 1)
	{
		if (munmap(zone->mmapStart, zone->size) == -1)
			return (void)(ft_printf("Error: munmap failed\n"));
	}
	if (head && head->size > all->M)
	{
		if (munmap(zone->mmapStart, zone->size) == -1)
			return (void)(ft_printf("Error: munmap failed\n"));
	}
	pthread_mutex_unlock(&mutex);
}