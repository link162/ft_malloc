/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   realloc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybuhai <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/19 02:59:51 by ybuhai            #+#    #+#             */
/*   Updated: 2020/01/27 20:48:19 by ybuhai           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_malloc_internal.h"

void	write_history(t_func func, size_t size)
{
	t_hist *hist;

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

void	show_alloc_mem_ex(void)
{
	t_hist *hist;

	hist = g_mem.hist;
	ft_printf("Malloc history\n");
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

void	*concatinate_mem(void *ptr, size_t size, t_zone **zone, t_zone *obj)
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
	ft_memcpy(tmp, ptr, obj->size);
	free(ptr);
	pthread_mutex_unlock(&g_mutex);
	return (tmp);
}

void	*realloc(void *ptr, size_t size)
{
	t_zone **zone;

	pthread_mutex_lock(&g_mutex);
	if (is_global_var_set())
		write_history(F_REALLOC, size);
	if (!g_mem.tiny)
		mem_init();
	if (!size || !g_mem.tiny || !ptr)
	{
		free(ptr);
		pthread_mutex_unlock(&g_mutex);
		return (malloc(size));
	}
	if (NULL == (zone = find_zone(ptr, &g_mem.tiny)))
		if (NULL == (zone = find_zone(ptr, &g_mem.small)))
			if (NULL == (zone = find_zone(ptr, &g_mem.big)))
			{
				pthread_mutex_unlock(&g_mutex);
				return (NULL);
			}
	return (concatinate_mem(ptr, size, zone, *zone));
}
