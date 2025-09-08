/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   malloc.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eburnet <eburnet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/01 09:58:49 by eburnet           #+#    #+#             */
/*   Updated: 2025/09/04 15:08:39 by eburnet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "malloc.h"

static struct allocs *all;

// struct rlimit {
// 	rlim_t rlim_cur;  /* limite souple */
// 	rlim_t rlim_max;  /* limite stricte (plafond de rlim_cur) */
// };

// You are allowed a global variable to manage your allocations and one for the threadsafe (MUTEX).

struct allocs {
	struct zones	*tiny;
	struct zones	*small;
	struct zones	*large;
	const size_t N;
	const size_t M;
};
	
struct zones {
	void			*mmapStart;
	long			size;
	struct header	*header;
	void			*next;
};

struct header {
	int				is_free;
	unsigned long	size;
	void			*next;
};

findFreeZone(int sizeNeed, struct header *actualH)
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
}

void *findFreeSpace(int sizeNeed, int nm)
{
	struct rlimit rlim;
	struct zones *actualZone;
	struct header *actualH;
	ptrdiff_t remains;
	int memLim = getrlimit(RLIMIT_MEMLOCK, &rlim);
	if (nm == 0)
		actualZone = all->tiny;
	else
		actualZone = all->small;
	while (actualZone != NULL) {	
		actualH = actualZone->header;
		while (actualH != NULL) {
			findFreeZone(sizeNeed, actualH);
			actualH = actualH->next;
		}
		actualZone = actualZone->next;
	}
	actualH = actualZone->header;
	while (actualH->next != NULL)
		actualH = actualH->next;
	void *posX = (char*)actualH + sizeof(struct header) + actualH->size;
	if (nm == 0)
		remains = (char*)all->N - (char*)posX ;
	else
		remains = (char*)all->M - (char*)posX;
	if (remains < 0)
		return (NULL); // error
	size_t remaining_space = (size_t)remains;
	int toAdd = 8 - (sizeNeed % 8);
	int roundSize;
	if (toAdd == 8)
		roundSize = sizeNeed;
	else
		roundSize = sizeNeed + toAdd;
	if (remaining_space < (roundSize + sizeof(struct header)))
		return (NULL);
	
	// sinon aller a cursor de actualZone
		// decouper un bloc a la taille
		// modifier le header
		// retour
}

void *malloc(size_t size)
{
	// si size == 1 == 1 bytes (octets), 8 bits
	const int n = 512;
	const int m = 4096;
	void *res;
	const long pageSize = sysconf(_SC_PAGESIZE);
	all->M = (((m * 100) + pageSize - 1) / pageSize) * pageSize; // m x100 arrondie au superieur
	all->N = (((n * 100) + pageSize - 1) / pageSize) * pageSize; // n x100 arrondie au superieur
	if (size <= n) {
		res = findFreeSpace(size, 0);
		if (res != NULL)
			return(res);
		void *alocZone = mmap(NULL, all->N , PROT_READ|PROT_WRITE, MAP_PRIVATE|MAP_ANONYMOUS, -1, 0);
		if (alocZone == MAP_FAILED)
			perror("mmap"), exit(1);
		return(findFreeSpace(size, n));
	} 
	else if (size <= m) {
		res = findFreeSpace(size, 1);
		if (res != NULL)
			return(res);
		void *alocZone = mmap(NULL, all->M , PROT_READ|PROT_WRITE, MAP_PRIVATE|MAP_ANONYMOUS, -1, 0);
		if (alocZone == MAP_FAILED)
			perror("mmap"), exit(1);
		return(findFreeSpace(size, n));
	}
	else {
		void *largeZone = mmap(NULL, size, PROT_READ|PROT_WRITE, MAP_PRIVATE|MAP_ANONYMOUS, -1, 0);
		return (largeZone);
	}
}
