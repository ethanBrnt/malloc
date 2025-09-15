/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   malloc.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eburnet <eburnet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/08 12:47:41 by eburnet           #+#    #+#             */
/*   Updated: 2025/09/15 15:13:44 by eburnet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#define _GNU_SOURCE
#include "libft/libft.h"
#include <stdlib.h>
#include <sys/time.h>
#include <sys/resource.h>
#include <unistd.h>
#include <sys/mman.h>
#include <stddef.h>

#define n 512
#define m 4096

void my_free(void *ptr);
void *my_malloc(size_t size);
void *realloc(void *ptr, size_t size);
void show_alloc_mem();


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
	 struct zones	*next;
};

struct header {
	int				is_free;
	int				size;
	struct header	*next;
};