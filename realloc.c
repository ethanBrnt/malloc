/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   realloc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eburnet <eburnet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/15 15:05:22 by eburnet           #+#    #+#             */
/*   Updated: 2026/06/10 17:59:02 by eburnet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "malloc.h"

zones_t *get_zone_from_ptr(void *ptr)
{
	zones_t *current = all.large; 

	while (current)
	{
		void *start = current->mmapStart;
		void *end = current->mmapStart + current->size;
		if (ptr >= start && ptr <= end)
			return (current);
		current = current->next;
	}
	return (NULL);
}

void *realloc(void *ptr, size_t size)
{
	if (ptr == NULL)
		return (malloc(size));    
	else if (size == 0)
		return (free(ptr), NULL);
	pthread_mutex_lock(&mutex);
	size_t copy_size;
	header_t *head = (header_t*)ptr - 1;
	zones_t *zone = get_zone_from_ptr(ptr);
	if (zone == NULL)
	{
		if (head->size < size)
			copy_size = head->size;
		else if (head->size == size)
			return (pthread_mutex_unlock(&mutex), ptr);
		else
			copy_size = size;
	}
	else
	{
		if (zone->size < size)
			copy_size = zone->size;
		else if (zone->size == size)
			return (pthread_mutex_unlock(&mutex), ptr);
		else
			copy_size = size;
	}

	pthread_mutex_unlock(&mutex);
	void *new_ptr = malloc(size);
	pthread_mutex_lock(&mutex);

	ft_memcpy(new_ptr, ptr, copy_size);
	pthread_mutex_unlock(&mutex);
	free(ptr);
	return (new_ptr);
}
