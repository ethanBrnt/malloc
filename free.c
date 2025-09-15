/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eburnet <eburnet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/15 14:18:40 by eburnet           #+#    #+#             */
/*   Updated: 2025/09/15 14:40:52 by eburnet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "malloc.h"

void my_free(void *ptr)
{
    if (ptr == NULL)
        return ;
    struct header *head = ptr - sizeof(struct header);
    if (!head)
        return ;
    head->is_free = 1;
}