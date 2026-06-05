/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eburnet <eburnet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/15 14:18:40 by eburnet           #+#    #+#             */
/*   Updated: 2026/06/05 15:44:58 by eburnet          ###   ########.fr       */
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
	// ft_printf("my free\n");
	if (ptr == NULL)
		return ;
	pthread_mutex_lock(&mutex);
	zones_t *zone = findPtr(ptr);
	if (zone == NULL)
		return (void)(pthread_mutex_unlock(&mutex));
	// if (zone->size <= all->N)
	// 	ft_printf("tiny free\n");
	// else if (zone->size <= all->M)
	// 	ft_printf("small free\n");
	// else
	// 	ft_printf("Large free\n");
	header_t *head = (header_t*)ptr - 1;
	if (head->is_free == true)
		return (void)(pthread_mutex_unlock(&mutex));
	head->is_free = true;
	// ft_printf("all tiny: %p, small: %p\n", all->tiny, all->small);
	zones_t *prev_zone = findPrevZone(zone);
	if (prev_zone)
		prev_zone->next = zone->next;
	else
	{
		if (zone->size <= all->N)
			all->tiny = zone->next;
		else if (zone->size <= all->M)
			all->small = zone->next;
		else
			all->large = zone->next;
	}
	if (head && head->size <= m && is_zone_empty(zone) == 1) {
		// ft_printf("all tiny: %p, small: %p\n", all->tiny, all->small);
		if (munmap(zone->mmapStart, zone->size) == -1)
			return (void)(ft_putstr_fd("Error: munmap failed\n", 2));
	}
	else if (zone->size > m) {
		ft_printf("free large munmap\n");
		if (munmap(zone->mmapStart, zone->size) == -1)
			return (void)(ft_putstr_fd("Error: munmap failed\n", 2));
	}
	pthread_mutex_unlock(&mutex);
}