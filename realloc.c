/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   realloc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eburnet <eburnet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/15 15:05:22 by eburnet           #+#    #+#             */
/*   Updated: 2026/06/03 14:03:23 by eburnet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "malloc.h"

void *realloc(void *ptr, size_t size)
{
	if (ptr == NULL)
		return (malloc(size));    
	else if (size == 0)
		return (free(ptr), NULL);
	header_t *head = (header_t*)ptr - 1;
	if (head->size >= size)
		return (ptr);
	else {
		void *new_ptr = malloc(size);
		size_t copy_size = (head->size < size) ? (size_t)head->size : size;
		pthread_mutex_lock(&mutex);
		ft_memcpy(new_ptr, ptr, copy_size);
		pthread_mutex_unlock(&mutex);
		free(ptr);
		return (new_ptr);
	}
}