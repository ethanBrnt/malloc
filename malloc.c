/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   malloc.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eburnet <eburnet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/01 09:58:49 by eburnet           #+#    #+#             */
/*   Updated: 2026/06/05 12:47:13 by eburnet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "malloc.h"
allocs_t *all;
pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;

void *cutRemaining(header_t *prevHeader, int sizeNeed, zones_t *actualZone)
{
	// ft_putstr("cutRemaining\n");	
	void *nextPos = actualZone->mmapStart;
	if (prevHeader != NULL)
		nextPos = (char*)prevHeader + sizeof(header_t) + prevHeader->size;
	ptrdiff_t remains = ((char*)actualZone->mmapStart + actualZone->size) - (char*)nextPos;
	if (remains < 0)
		return (NULL);
	size_t remaining_space = (size_t)remains;

	int toAdd = 8 - (sizeNeed % 8);
	if (toAdd == 8)
		toAdd = 0;
	int roundSize = sizeNeed + toAdd;
	if (remaining_space < (roundSize + sizeof(header_t)))
		return (NULL);

	header_t *newHeader = (header_t *)nextPos;
	newHeader->is_free = false;
	newHeader->size = roundSize;
	newHeader->next = NULL;
	if (prevHeader != NULL)
		prevHeader->next = newHeader;
	else
		actualZone->header = newHeader;
	return ((char*)newHeader + sizeof(header_t));
}

void *isZoneFree(int sizeNeed, header_t *actualH)
{
	int toAdd = 8 - (sizeNeed % 8);
	if (toAdd == 8)
		toAdd = 0;
	int roundSize = sizeNeed + toAdd;
	if (actualH->is_free == true && (size_t)roundSize <= actualH->size) {
		actualH->is_free = false;
		actualH->size = roundSize;
		// ft_putstr("findFreeZone return something\n");
		return ((char*)actualH + sizeof(header_t));
	}
	return (NULL);
}

void *findSpace(int sizeNeed)
{
	// ft_putstr("findSpace\n");
	zones_t *actualZone;
	header_t *actualHead;
	header_t *prevHead = NULL;
	void *res;

	if (sizeNeed <= n)
		actualZone = all->tiny;
	else
		actualZone = all->small;
	if (actualZone == NULL)
		return (NULL);
	while (actualZone != NULL) {
		actualHead = actualZone->header;
		while (actualHead != NULL) {
			prevHead = actualHead;
			res = isZoneFree(sizeNeed, actualHead);
			if (res != NULL)
				return (res);
			actualHead = actualHead->next;
		}
		res = cutRemaining(prevHead, sizeNeed, actualZone);
		if (res != NULL)
			return (res);
		actualZone = actualZone->next;
	}
	return (NULL);
}

void *initNewZone(int toAlloc, void *alocZone)
{
	zones_t *newZone = mmap(NULL, sizeof(zones_t), PROT_READ|PROT_WRITE, MAP_PRIVATE|MAP_ANONYMOUS, -1, 0);
	if (newZone == MAP_FAILED)
		return(ft_putstr_fd("Error: mmap newzone", 2), pthread_mutex_unlock(&mutex), NULL);
	newZone->mmapStart = alocZone;
	newZone->size = toAlloc;
	newZone->header = NULL;
	newZone->next = NULL;
	return (newZone);
}

void *createZone(zones_t *lastZone, int toAlloc, size_t size)
{
	// ft_printf("_New mmap zone_ %d\n", toAlloc);
	void *alocZone = mmap(NULL, toAlloc, PROT_READ|PROT_WRITE, MAP_PRIVATE|MAP_ANONYMOUS, -1, 0);
	if (alocZone == MAP_FAILED)
		return (ft_putstr_fd("Error: mmap alocZone", 2), pthread_mutex_unlock(&mutex), NULL);
	zones_t *newZone = initNewZone(toAlloc, alocZone);
	if (lastZone == NULL) {
		if ((int)size <= n)
			all->tiny = newZone;
		else if ((int)size > n && (int)size <= m)
			all->small = newZone;
		else
			all->large = newZone;
	}
	else {
		while (lastZone->next)
			lastZone = lastZone->next;
		lastZone->next = newZone;
	}
	if ((int)size > m) {
		return (pthread_mutex_unlock(&mutex), (char*)alocZone + sizeof(header_t));
	}
	else
		return(pthread_mutex_unlock(&mutex), findSpace(size));
}

void	initAllocs()
{
	const long pageSize = sysconf(_SC_PAGESIZE);
	if (!all) {
		all = mmap(NULL, sizeof(allocs_t), PROT_READ|PROT_WRITE, MAP_PRIVATE|MAP_ANONYMOUS, -1, 0);
		if (all == MAP_FAILED)
			return (void)(ft_putstr_fd("Error: mmap struc alloc", 2), pthread_mutex_unlock(&mutex));
		all->tiny = NULL;
		all->small = NULL;
		all->large = NULL;
		all->N = ((((n + sizeof(header_t)) * 100) + pageSize - 1) / pageSize) * pageSize; // n x100 arrondie au superieur
		all->M = ((((m + sizeof(header_t)) * 100) + pageSize - 1) / pageSize) * pageSize; // m x100 arrondie au superieur
	}
}

void *malloc(size_t size)
{
	// ft_printf("my malloc\n");
	zones_t *lastZone;
	int toAlloc;
	
	pthread_mutex_lock(&mutex);
	initAllocs();
	if (size <= 0)
		return (pthread_mutex_unlock(&mutex), NULL);
	if ((int)size <= n)
		toAlloc = all->N, lastZone = all->tiny;
	else if ((int)size > n && (int)size <= m)
		toAlloc = all->M, lastZone = all->small;
	else if ((int)size > m)
		toAlloc = size + sizeof(header_t), lastZone = all->large;
	if ((int)size <= m)	{
		void *res = findSpace(size);
		if (res != NULL)
			return (pthread_mutex_unlock(&mutex), res);
	}
	return (createZone(lastZone, toAlloc, size));
}
