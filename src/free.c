/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybuhai <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/19 03:09:31 by ybuhai            #+#    #+#             */
/*   Updated: 2020/01/25 20:14:59 by ybuhai           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_malloc_internal.h"

void	*calloc(size_t count, size_t size)
{
	void *tmp;

	tmp = malloc(count * size);
	if (tmp)
		ft_bzero(tmp, count * size);
	return (tmp);
}

void	show_alloc_mem(void)
{
	t_zone *zone;

	pthread_mutex_lock(&g_mutex);
	zone = g_mem.tiny;
	while (zone)
	{
		if (zone->used == FOR_MEM)
			ft_printf("Zone %p size %llu\n", zone, zone->size);
		zone = zone->next;
	}
	zone = g_mem.small;
	while (zone)
	{
		if (zone->used == FOR_MEM)
			ft_printf("Zone %p size %llu\n", zone, zone->size);
		zone = zone->next;
	}
	zone = g_mem.big;
	while (zone)
	{
		if (zone->used == FOR_MEM)
			ft_printf("Zone %p size %llu\n", zone, zone->size);
		zone = zone->next;
	}
	pthread_mutex_unlock(&g_mutex);
}

int		find_ptr_in_list(t_zone *zone, void *ptr)
{
	t_zone *t;

	t = NULL;
	while (zone)
	{
		if (zone + 1 == ptr)
		{
			zone->used = 0;
			if (zone->next && !zone->next->used && zone->next ==
					(void *)zone + zone->size + sizeof(t_zone))
			{
				zone->size += zone->next->size + sizeof(t_zone);
				zone->next = zone->next->next;
			}
			if (t && !t->used && (void *)t + t->size + sizeof(t_zone) == zone)
			{
				t->size += zone->size + sizeof(t_zone);
				t->next = zone->next;
			}
			return (1);
		}
		t = zone;
		zone = zone->next;
	}
	return (0);
}

void	free_ptr_in_big(t_zone **zone, void *ptr)
{
	t_zone *tmp;
	t_zone *tail;

	if ((*zone) + 1 == ptr)
	{
		tmp = (*zone)->next;
		munmap((void *)*zone, (*zone)->size + sizeof(t_zone));
		*zone = tmp;
		return ;
	}
	tmp = *zone;
	while (tmp->next)
	{
		if (tmp->next + 1 == ptr)
		{
			tail = tmp->next->next;
			munmap((void *)tmp->next, tmp->next->size + sizeof(t_zone));
			tmp->next = tail;
			return ;
		}
		tmp = tmp->next;
	}
}

void	free(void *ptr)
{
	pthread_mutex_lock(&g_mutex);
	if (!issetugid())
		if (getenv("MallocStackLogging"))
			write_history(F_FREE, 0);
	if (!ptr)
	{
		pthread_mutex_unlock(&g_mutex);
		return ;
	}
	if (!find_ptr_in_list(g_mem.tiny, ptr))
		if (!find_ptr_in_list(g_mem.small, ptr))
			free_ptr_in_big(&g_mem.big, ptr);
	pthread_mutex_unlock(&g_mutex);
}
