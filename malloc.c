/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   malloc.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eburnet <eburnet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/01 09:58:49 by eburnet           #+#    #+#             */
/*   Updated: 2025/09/09 15:01:30 by eburnet          ###   ########.fr       */
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

void *findCut(struct header *actualHead, int sizeNeed, int toAlloc, void *posX)
{
	ft_putstr("findCut\n");
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
		ft_putstr("ici\n");
		if (remains < 0)
			ft_putstr_fd("Error: findCut conversion", 2), exit(1);
		remaining_space = (size_t)remains;
	}
	else
		remaining_space = toAlloc * 2;
	ft_putstr("here\n");
	int toAdd = 8 - (sizeNeed % 8);
	int roundSize;
	if (toAdd == 8)
		toAdd = 0;
	roundSize = sizeNeed + toAdd;
	if (remaining_space < (roundSize + sizeof(struct header)))
		return (NULL);
	ft_putstr("there\n");

	struct header *newHeader = (struct header *)posX;
	newHeader->is_free = 0;
	newHeader->size = roundSize;
	newHeader->next = NULL;
	if (actualHead != NULL)
		prevHeader->next = newHeader;
	ft_putstr("before last return\n");
	return ((char*)newHeader + sizeof(struct header));
}

void *findFreeZone(int sizeNeed, struct header *actualH)
{
	ft_putstr("findFreeZone\n");
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
	{
		ft_putstr("actualZone is NULL\n");
		return (NULL);
	}
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
		res = findCut(prevHead, sizeNeed, toAlloc, actualZone->mmapStart);
		if (res != NULL)
			return (res);
		actualZone = actualZone->next;
	}
	return (NULL);
}

// TODO opti if else
void *my_malloc(size_t size)
{
	// si size == 1 == 1 byte (octet), 8 bits
	ft_putstr("mon malloc\n");
	if (!all) {
		all = mmap(NULL, sizeof(struct allocs), PROT_READ | PROT_WRITE,
				MAP_PRIVATE | MAP_ANONYMOUS, -1, 0);
		if (all == MAP_FAILED)
			ft_putstr_fd("Error: mmap struc alloc", 2), exit(1);
	}
	const int n = 512;
	const int m = 4096;
	const long pageSize = sysconf(_SC_PAGESIZE);
	all->M = (((m * 100) + pageSize - 1) / pageSize) * pageSize; // m x100 arrondie au superieur
	all->N = (((n * 100) + pageSize - 1) / pageSize) * pageSize; // n x100 arrondie au superieur
	void *res;
	int toAlloc = m;
	struct zones *lastZone = all->small;
	struct zones *newZone = mmap(NULL, sizeof(struct zones), PROT_READ|PROT_WRITE, MAP_PRIVATE|MAP_ANONYMOUS, -1, 0);
	if (newZone == MAP_FAILED)
		ft_putstr_fd("Error: mmap newzone", 2), exit(1);

	if ((int)size <= m) {
		if ((int)size <= n)
			toAlloc = n, lastZone = all->tiny, ft_putstr("---TINY---\n");
		res = findFreeSpace(size, toAlloc);
		if (res != NULL)
			return(res);
		void *alocZone = mmap(NULL, toAlloc , PROT_READ|PROT_WRITE, MAP_PRIVATE|MAP_ANONYMOUS, -1, 0);
		if (alocZone == MAP_FAILED)
			ft_putstr_fd("Error: mmap alocZone", 2), exit(1);
		newZone->mmapStart = alocZone;
		newZone->size = toAlloc;
		newZone->header = NULL;
		newZone->next = NULL;
		if (!lastZone) {
			ft_putstr("Premiere zone de cette taille\n");
			if ((int)size <= n)
				all->tiny = newZone;
			else
				all->small = newZone;
		} else {
			while (lastZone->next)
				lastZone = lastZone->next;
			lastZone->next = newZone;
		}
		return(findFreeSpace(size, toAlloc));
	}
	else {
		ft_putstr("---LARGE---\n");
		lastZone = all->large;
		void *largeZone = mmap(NULL, size, PROT_READ|PROT_WRITE, MAP_PRIVATE|MAP_ANONYMOUS, -1, 0);
		if (largeZone == MAP_FAILED)
			ft_putstr_fd("Error: mmap largezone", 2), exit(1);

		newZone->mmapStart = largeZone;
		newZone->size = size;
		newZone->header = NULL;
		newZone->next = NULL;
		if (!lastZone) {
			ft_putstr("Premiere zone large\n");
			if ((int)size <= n)
				all->tiny = newZone;
			else
				all->small = newZone;
		} else {
			while (lastZone->next)
				lastZone = lastZone->next;
			lastZone->next = newZone;
		}
		return (largeZone);
	}
}
