#include "ft_malloc_internal.h"

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

void	*realloc(void *ptr, size_t size)
{
	//ft_printf("realloc(%p, %lli);\n", ptr, size);
	t_zone **zone;
	t_zone *tmp;
	void *ret;

	pthread_mutex_lock(&mutex);
	if (size < 0)
	{
		pthread_mutex_unlock(&mutex);
		return (NULL);
	}
	if (!size || !g_mem.tiny)
	{
		free(ptr);
		pthread_mutex_unlock(&mutex);
		return (malloc(size));
	}
	zone = find_zone(ptr, &g_mem.tiny);
	if (!zone)
		zone = find_zone(ptr, &g_mem.small);
	if (!zone)
		zone = find_zone(ptr, &g_mem.big);
	if (!zone || !ptr)
	{
		pthread_mutex_unlock(&mutex);
		return (malloc(size));
	}
	if ((*zone)->size >= size)
	{
		pthread_mutex_unlock(&mutex);
		return (ptr);
	}
	if ((*zone)->next && !(*zone)->next->used && (*zone)->size + (*zone)->next->size + sizeof(t_zone) >= size)
	{
		(*zone)->size += (*zone)->next->size + sizeof(t_zone);
		(*zone)->next = (*zone)->next->next;
		pthread_mutex_unlock(&mutex);
		return (ptr);
	}
	t_zone *obj = *zone;
	tmp = malloc(size);
	if (!tmp)
	{
		pthread_mutex_unlock(&mutex);
		return (NULL);
	}
	ft_memcpy(tmp, ptr, obj->size);
	free(ptr);
	pthread_mutex_unlock(&mutex);
	return (tmp);
}
