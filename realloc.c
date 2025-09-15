/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   realloc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eburnet <eburnet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/15 15:05:22 by eburnet           #+#    #+#             */
/*   Updated: 2025/09/15 16:03:03 by eburnet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "malloc.h"

void *realloc(void *ptr, size_t size)
{
    if (ptr == NULL)
        retun (my_malloc(size));    
    if (size == 0)
        return (my_free(ptr), NULL);
    struct header *head = ptr - sizeof(struct header);
    if (!head)
        return (NULL);
    if ((head->size <= n && size <= n) || (head->size <= m && size <= m))
        head->size = size;
    else if ((head->size <= n && size > n) || (head->size <= m && size > m)
            || (head->size > n && size <= n) || (head->size > m && size <= m))
    {
        void *new_ptr = my_malloc(size);
        if (ft_memcpy(new_ptr, ptr, size) != NULL)
            head->is_free = 1;
        return (new_ptr);
    }
    return (ptr);
    //si deplacement finir par set is free a 1 si tout c'est bien passer
}