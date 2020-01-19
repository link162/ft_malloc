/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   realloc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybuhai <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/19 02:59:51 by ybuhai            #+#    #+#             */
/*   Updated: 2020/01/19 04:35:01 by ybuhai           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_malloc_internal.h"

void	write_history(t_func func, size_t size)
{
	t_hist *hist;

	if (HISTORY_EN)
		return ;
	if (!g_mem.tiny)
		mem_init();
	if (!g_mem.hist)
	{
		g_mem.hist = find_memory(sizeof(t_hist), g_mem.tiny, 1, FOR_POOL);
		if (!g_mem.hist)
			return ;
		g_mem.hist->size = size;
		g_mem.hist->func = func;
		g_mem.hist->next = NULL;
		return ;
	}
	hist = g_mem.hist;
	while (hist->next)
		hist = hist->next;
	hist->next = find_memory(sizeof(t_hist), g_mem.tiny, 1, FOR_POOL);
	if (!hist->next)
		return ;
	hist->next->size = size;
	hist->next->func = func;
	hist->next->next = NULL;
}

void	malloc_show_history(void)
{
	t_hist *hist;

	hist = g_mem.hist;
	while (hist)
	{
		if (hist->func == F_MALLOC)
			ft_printf("malloc: %llu\n", hist->size);
		else if (hist->func == F_FREE)
			ft_printf("free:\n");
		else if (hist->func == F_REALLOC)
			ft_printf("realloc: %llu\n", hist->size);
		hist = hist->next;
	}
}

t_zone	**find_zone(void *ptr, t_zone **zone)
{
	t_zone *tmp;

	if ((*zone) + 1 == ptr)
		return (zone);
	tmp = *zone;
	while (tmp->next)
	{
		if (tmp->next + 1 == ptr)
			return (&tmp->next);
		tmp = tmp->next;
	}
	return (NULL);
}

void	*find_memory_for_realloc(void *ptr, size_t size, t_zone **zone)
{
	void *tmp;

	if ((*zone)->size >= size)
	{
		pthread_mutex_unlock(&g_mutex);
		return (ptr);
	}
	if ((*zone)->next && !(*zone)->next->used && (*zone)->size +
			(*zone)->next->size + sizeof(t_zone) >= size)
	{
		(*zone)->size += (*zone)->next->size + sizeof(t_zone);
		(*zone)->next = (*zone)->next->next;
		pthread_mutex_unlock(&g_mutex);
		return (ptr);
	}
	tmp = malloc(size);
	if (!tmp)
	{
		pthread_mutex_unlock(&g_mutex);
		return (NULL);
	}
	ft_memcpy(tmp, ptr, (*zone)->size);
	free(ptr);
	pthread_mutex_unlock(&g_mutex);
	return (tmp);
}

void	*realloc(void *ptr, size_t size)
{
	t_zone **zone;

	pthread_mutex_lock(&g_mutex);
	if (!g_mem.tiny)
		mem_init();
	if (HISTORY_EN)
		write_history(F_REALLOC, size);
	if (!size || !g_mem.tiny)
	{
		free(ptr);
		pthread_mutex_unlock(&g_mutex);
		return (malloc(size));
	}
	zone = find_zone(ptr, &g_mem.tiny);
	if (!zone)
		zone = find_zone(ptr, &g_mem.small);
	if (!zone)
		zone = find_zone(ptr, &g_mem.big);
	if (!zone || !ptr)
	{
		pthread_mutex_unlock(&g_mutex);
		return (malloc(size));
	}
	return (find_memory_for_realloc(ptr, size, zone));
}
