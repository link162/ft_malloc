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
	ft_printf("realloc(%p, %lli);\n",ptr, size);
	t_zone **zone;
	t_zone *tmp;

	if (size < 0)
		return (NULL);
	if (!size)
	{
		free(ptr);
		return (malloc(size));
	}
	zone = find_zone(ptr, &g_mem.tiny);
	if (!zone)
		zone = find_zone(ptr, &g_mem.small);
	if (!zone)
		zone = find_zone(ptr, &g_mem.big);
	if (!zone || !ptr)
		return (malloc(size));
	if ((*zone)->size >= size)
		return (ptr);
	if ((*zone)->next && !(*zone)->next->used && (*zone)->size + (*zone)->next->size + sizeof(t_zone) >= size)
	{
		(*zone)->size += (*zone)->next->size + sizeof(t_zone);
		(*zone)->next = (*zone)->next->next;
		return (ptr);
	}
	t_zone *obj = *zone;
	tmp = malloc(size);
	if (!tmp)
		return (NULL);
	ft_memcpy(tmp, ptr, obj->size);
	free(ptr);
	return (tmp);
}
