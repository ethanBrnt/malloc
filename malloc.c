/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   malloc.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eburnet <eburnet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/01 09:58:49 by eburnet           #+#    #+#             */
/*   Updated: 2025/09/10 14:24:10 by eburnet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "malloc.h"

static struct allocs *all;

// You are allowed a global variable to manage your allocations and one for the threadsafe (MUTEX).

struct allocs {
	struct zones	*tiny;
	struct zones	*small;
	struct zones	*large;
	size_t N;
	size_t M;
	int n;
	int m;
};

struct zones {
	void			*mmapStart;
	long			size;
	struct header	*header;
	void			*next;
};

struct header {
	int		is_free;
	int		size;
	void	*next;
};

void *remainingCut(struct header *actualHead, int sizeNeed, int toAlloc, void *posX)
{
	ptrdiff_t remains;
	size_t remaining_space;
	struct header *prevHeader;
	if (actualHead != NULL)
	{
		prevHeader = actualHead;
		posX = (char*)actualHead + sizeof(struct header) + actualHead->size;
		if (toAlloc == 512)
			remains = (char*)all->N - (char*)posX ;
		else
			remains = (char*)all->M - (char*)posX;
		if (remains < 0)
			ft_putstr_fd("Error: findCut conversion", 2), exit(1);
		remaining_space = (size_t)remains;
	}
	else
		remaining_space = toAlloc;

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
	if (actualHead != NULL)
		prevHeader->next = newHeader;
	return ((char*)newHeader + sizeof(struct header));
}

void *findFreeZone(int sizeNeed, struct header *actualH)
{
	int toAdd = 8 - (sizeNeed % 8);
	int roundSize;

	if (toAdd == 8)
		roundSize = sizeNeed;
	else
		roundSize = sizeNeed + toAdd;
	if (actualH->is_free && actualH->size >= roundSize) {
		actualH->is_free = 0;
		actualH->size = roundSize;
		// DECOUPAGE ??
		return ((char*)actualH + sizeof(struct header));
	}
	return (NULL);
}

void *findFreeSpace(int sizeNeed, int toAlloc)
{
	ft_putstr("findFreeSpace\n");
	// struct rlimit rlim;
	struct zones *actualZone;
	struct header *actualHead;
	struct header *prevHead = NULL;
	void *res;

	// int memLim = getrlimit(RLIMIT_MEMLOCK, &rlim);
	if (toAlloc == 512)
		actualZone = all->tiny;
	else
		actualZone = all->small;
	if (actualZone == NULL)
		return (ft_putstr("actualZone is NULL\n"), NULL);
	while (actualZone != NULL) {
		actualHead = actualZone->header;
		while (actualHead != NULL) {
			res = findFreeZone(sizeNeed, actualHead);
			if (res != NULL)
				return (res);
			prevHead = actualHead;
			actualHead = actualHead->next;
		}
		res = NULL;
		res = remainingCut(prevHead, sizeNeed, toAlloc, actualZone->mmapStart);
		if (res != NULL)
			return (res);
		actualZone = actualZone->next;
	}
	return (NULL);
}

void	initAllocs()
{
	if (!all) {
		all = mmap(NULL, sizeof(struct allocs), PROT_READ | PROT_WRITE, MAP_PRIVATE | MAP_ANONYMOUS, -1, 0);
		if (all == MAP_FAILED)
		ft_putstr_fd("Error: mmap struc alloc", 2), exit(1);
	}
	const long pageSize = sysconf(_SC_PAGESIZE);
	all->m = 4096;
	all->n = 512;
	all->N = (((all->n * 100) + pageSize - 1) / pageSize) * pageSize; // n x100 arrondie au superieur
	all->M = (((all->m * 100) + pageSize - 1) / pageSize) * pageSize; // m x100 arrondie au superieur

}


void *my_malloc(size_t size)
{
	initAllocs();
 	struct zones *newZone = mmap(NULL, sizeof(struct zones), PROT_READ|PROT_WRITE, MAP_PRIVATE|MAP_ANONYMOUS, -1, 0);
	if (newZone == MAP_FAILED)
		ft_putstr_fd("Error: mmap newzone", 2), exit(1);
	struct zones *lastZone = all->tiny;
	int toAlloc = all->n;
	void *alocZone;
	void *res;

	if ((int)size <= all->m)
		toAlloc = all->m, lastZone = all->small;
	else if ((int)size > all->m)
		toAlloc = size, lastZone = all->large;
	if (size < all->m)
	{
		res = findFreeSpace(size, toAlloc);
		if (res != NULL)
			return(res);
	}
	alocZone = mmap(NULL, toAlloc , PROT_READ|PROT_WRITE, MAP_PRIVATE|MAP_ANONYMOUS, -1, 0);
	if (alocZone == MAP_FAILED)
		ft_putstr_fd("Error: mmap alocZone", 2), exit(1);
	newZone->mmapStart = alocZone;
	newZone->size = toAlloc;
	newZone->header = NULL;
	newZone->next = NULL;
	if (!lastZone) {
		ft_putstr("Premiere zone de cette taille\n");
		if ((int)size <= all->n)
			all->tiny = newZone;
		else if (((int)size <= all->m))
			all->small = newZone;
		else
			all->large = newZone;
	} else {
		while (lastZone->next)
			lastZone = lastZone->next;
		lastZone->next = newZone;
	}
	if (size > all->m)
		return (alocZone);
	else
		return(findFreeSpace(size, toAlloc));
}
