/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   malloc.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eburnet <eburnet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/08 12:47:41 by eburnet           #+#    #+#             */
/*   Updated: 2025/09/09 11:43:55 by eburnet          ###   ########.fr       */
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

void free(void *ptr);
void *my_malloc(size_t size);
void *realloc(void *ptr, size_t size);
void show_alloc_mem();
