/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   malloc.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eburnet <eburnet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/08 12:47:41 by eburnet           #+#    #+#             */
/*   Updated: 2026/06/11 09:29:22 by eburnet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#define _GNU_SOURCE
#include "libft/libft.h"
#include <sys/time.h>
#include <sys/resource.h>
#include <unistd.h>
#include <sys/mman.h>
#include <stddef.h>
#include <pthread.h>
#include <stdbool.h>

#define n 512
#define m 4096

void free(void *ptr);
void *malloc(size_t size);
void *realloc(void *ptr, size_t size);
void show_alloc_mem();

typedef struct allocs {
	struct zones	*tiny;
	struct zones	*small;
	struct zones	*large;
	size_t N;
	size_t M;
} allocs_t;

typedef struct zones {
	void			*mmapStart;
	size_t			size;
	struct header	*header;
	struct zones	*next;
} zones_t;

typedef struct header {
	size_t			size;
	struct header	*next;
	int				is_free;
	int				padding[3];
} header_t;

extern allocs_t all;

extern pthread_mutex_t mutex;
