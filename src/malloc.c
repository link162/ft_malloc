/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   malloc.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybuhai <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/19 02:50:27 by ybuhai            #+#    #+#             */
/*   Updated: 2020/01/26 21:04:41 by ybuhai           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_malloc_internal.h"

t_mem g_mem = {0, 0, 0, 0};
pthread_mutex_t g_mutex = PTHREAD_RECURSIVE_MUTEX_INITIALIZER;

void	*alloc_big_zone(size_t size, int pool)
{
	int		page_size;
	t_zone	*new;

	page_size = getpagesize();
	new = mmap(NULL, (size / page_size + 1) * page_size,
			PROT_READ | PROT_WRITE,
			MAP_ANONYMOUS | MAP_PRIVATE, -1, 0);
	if (new == MAP_FAILED)
		return (NULL);
	new->next = g_mem.big;
	new->size = (size / page_size + 1) * page_size - sizeof(t_zone);
	new->used = pool;
	g_mem.big = new;
	return ((void *)((void *)new) + sizeof(t_zone));
}

int		mem_init(void)
{
	if (!g_mem.tiny)
	{
		g_mem.tiny = (t_zone *)alloc_big_zone((TINY_SIZE + sizeof(t_zone)) *
				NUM_PRE_ALLOC + sizeof(t_zone), FOR_POOL);
		if (!g_mem.tiny)
			return (1);
		g_mem.tiny->size = (TINY_SIZE + sizeof(t_zone)) * NUM_PRE_ALLOC -
			sizeof(t_zone);
		g_mem.tiny->next = NULL;
		g_mem.tiny->used = 0;
	}
	if (!g_mem.small)
	{
		g_mem.small = (t_zone *)alloc_big_zone((SMALL_SIZE + sizeof(t_zone)) *
				NUM_PRE_ALLOC + sizeof(t_zone), FOR_POOL);
		if (!g_mem.small)
			return (1);
		g_mem.small->size = (SMALL_SIZE + sizeof(t_zone)) * NUM_PRE_ALLOC -
			sizeof(t_zone);
		g_mem.small->next = NULL;
		g_mem.small->used = 0;
	}
	return (0);
}

void	*allocate_more_memory(size_t size, t_zone *last, int tiny, int f_h)
{
	if (tiny)
		last->next = (t_zone *)alloc_big_zone((TINY_SIZE + sizeof(t_zone)) *
				NUM_PRE_ALLOC + sizeof(t_zone), FOR_POOL);
	else
		last->next = (t_zone *)alloc_big_zone((SMALL_SIZE + sizeof(t_zone)) *
				NUM_PRE_ALLOC + sizeof(t_zone), FOR_POOL);
	if (!last->next)
		return (NULL);
	last = last->next;
	last->size = size;
	last->used = f_h;
	last->next = (void *)last + size + sizeof(t_zone);
	last->next->size = (TINY_SIZE + sizeof(t_zone)) * NUM_PRE_ALLOC - size -
		sizeof(t_zone) * 2;
	last->next->used = 0;
	last->next->next = NULL;
	return ((void *)(last + 1));
}

void	*find_memory(size_t size, t_zone *zone, int tiny, int for_history)
{
	t_zone	*last;

	while (zone)
	{
		if (!zone->used && zone->size >= size)
		{
			zone->used = for_history;
			if (zone->size - size > sizeof(t_zone))
			{
				last = (void *)zone + size + sizeof(t_zone);
				last->size = zone->size - size - sizeof(t_zone);
				last->next = zone->next;
				zone->size = size;
				zone->next = last;
				last->used = 0;
			}
			return ((void *)zone + sizeof(t_zone));
		}
		last = zone;
		zone = zone->next;
	}
	return (allocate_more_memory(size, last, tiny, for_history));
}

void	*malloc(size_t size)
{
	void		*ret;
	long long	i;

	ret = NULL;
	if (!size)
		size = TINY_SIZE;
	i = size;
	if (i < 0)
		return (NULL);
	pthread_mutex_lock(&g_mutex);
	if (!g_mem.tiny || !g_mem.small)
		if (mem_init())
			ret = NULL;
	if (TINY_SIZE >= size)
		ret = find_memory(size, g_mem.tiny, 1, FOR_MEM);
	else if (SMALL_SIZE >= size)
		ret = find_memory(size, g_mem.small, 0, FOR_MEM);
	else
		ret = alloc_big_zone(size + sizeof(t_zone), FOR_MEM);
	if (is_global_var_set())
		write_history(F_MALLOC, size);
	pthread_mutex_unlock(&g_mutex);
	return (ret);
}
