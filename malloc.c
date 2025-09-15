/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   malloc.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eburnet <eburnet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/01 09:58:49 by eburnet           #+#    #+#             */
/*   Updated: 2025/09/15 15:14:31 by eburnet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "malloc.h"

static struct allocs *all;

void *remainingCut(struct header *prevHeader, int sizeNeed, struct zones *actualZone)
{
	ft_putstr("remainingCut\n");
	ptrdiff_t remains;
	size_t remaining_space;
	void *posX = actualZone->mmapStart;
	if (prevHeader != NULL)
	{
		// ft_printf("prevHeader->size: %d, %d, %d\n", prevHeader->size, sizeof(struct header), (char*)prevHeader);
		posX = (char*)prevHeader + sizeof(struct header) + prevHeader->size;
		remains = ((char*)actualZone->mmapStart + actualZone->size) - (char*)posX;
		// ft_printf("remains: %d, %d\n", remains, (char*)posX);
		if (remains < 0)
			return (NULL);
		remaining_space = (size_t)remains;
	}
	else
		remaining_space = sizeNeed * 2;

	int toAdd = 8 - (sizeNeed % 8);
	if (toAdd == 8)
		toAdd = 0;
	int roundSize = sizeNeed + toAdd;
	if (remaining_space < (roundSize + sizeof(struct header)))
		return (NULL);

	struct header *newHeader = (struct header *)posX;
	newHeader->is_free = 0;
	newHeader->size = roundSize;
	newHeader->next = NULL;
	if (prevHeader != NULL)
		prevHeader->next = newHeader;
	else
		actualZone->header = newHeader;
	return ((char*)newHeader + sizeof(struct header));
}

void *findFreeZone(int sizeNeed, struct header *actualH)
{
	// ft_putstr("findFreeZone\n");
	int toAdd = 8 - (sizeNeed % 8);
	if (toAdd == 8)
		toAdd = 0;
	int roundSize = sizeNeed + toAdd;
	if (actualH->is_free == 1 && actualH->size >= roundSize) {
		actualH->is_free = 0;
		actualH->size = roundSize;
		ft_putstr("findFreeZone return something\n");
		// DECOUPAGE ??
		return ((char*)actualH + sizeof(struct header));
	}
	return (NULL);
}

void *findFreeSpace(int sizeNeed)
{
	ft_putstr("findFreeSpace\n");
	// struct rlimit rlim;
	struct zones *actualZone;
	struct header *actualHead;
	struct header *prevHead = NULL;
	void *res;

	// int memLim = getrlimit(RLIMIT_MEMLOCK, &rlim);
	if (sizeNeed <= n)
		actualZone = all->tiny;
	else
		actualZone = all->small;
	if (actualZone == NULL)
		return (ft_putstr("actualZone is NULL\n"), NULL);
	while (actualZone != NULL) {
		prevHead = NULL;
		actualHead = actualZone->header;
		while (actualHead != NULL) {
			res = findFreeZone(sizeNeed, actualHead);
			if (res != NULL)
				return (res);
			prevHead = actualHead;
			actualHead = actualHead->next;
		}
		res = remainingCut(prevHead, sizeNeed, actualZone);
		if (res != NULL)
			return (res);
		actualZone = actualZone->next;
	}
	return (NULL);
}

void	initAllocs()
{
	const long pageSize = sysconf(_SC_PAGESIZE);
	if (!all) {
		all = mmap(NULL, sizeof(struct allocs), PROT_READ|PROT_WRITE, MAP_PRIVATE|MAP_ANONYMOUS, -1, 0);
		if (all == MAP_FAILED)
		ft_putstr_fd("Error: mmap struc alloc", 2), exit(1);
		all->tiny = NULL;
		all->small = NULL;
		all->large = NULL;
	}
	all->N = ((((n + sizeof(struct header)) * 100) + pageSize - 1) / pageSize) * pageSize; // n x100 arrondie au superieur
	all->M = ((((m + sizeof(struct header)) * 100) + pageSize - 1) / pageSize) * pageSize; // m x100 arrondie au superieur
}


void *my_malloc(size_t size)
{
	initAllocs();
	struct zones *lastZone;
	int toAlloc;

	if (size <= 0)
		return (NULL);
	if ((int)size <= n)
		toAlloc = all->N, lastZone = all->tiny;
	else if ((int)size > n && (int)size <= m)
		toAlloc = all->M, lastZone = all->small;
	else if ((int)size > m)
		toAlloc = size, lastZone = all->large;
	if ((int)size <= m)	{
		void *res = findFreeSpace(size);
		if (res != NULL)
			return(res);
	}
	ft_printf("_New mmap zone_ %d\n", toAlloc);
	void *alocZone = mmap(NULL, toAlloc , PROT_READ|PROT_WRITE, MAP_PRIVATE|MAP_ANONYMOUS, -1, 0);
	if (alocZone == MAP_FAILED)
		ft_putstr_fd("Error: mmap alocZone", 2), exit(1);
	struct zones *newZone = mmap(NULL, sizeof(struct zones), PROT_READ|PROT_WRITE, MAP_PRIVATE|MAP_ANONYMOUS, -1, 0);
	if (newZone == MAP_FAILED)
		ft_putstr_fd("Error: mmap newzone", 2), exit(1);
	newZone->mmapStart = alocZone;
	newZone->size = toAlloc;
	newZone->header = NULL;
	newZone->next = NULL;
	if (!lastZone) {
		ft_putstr("Premiere zone de cette taille\n");
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
	if ((int)size > m)
		return (alocZone);
	else
		return(findFreeSpace(size));
}
