#include "ft_malloc_internal.h"

int		 find_ptr_in_list(t_zone *zone, void *ptr)
{
	t_zone *tmp;

	tmp = NULL;
	while(zone)
	{
		if (zone + 1 == ptr)
		{
			zone->used = 0;
			if (zone->next && !zone->next->used)
			{
				zone->size += zone->next->size + sizeof(t_zone);
				zone->next = zone->next->next;
			}
			if (tmp && !tmp->used)
			{
				tmp->size += zone->size + sizeof(t_zone);
				tmp->next = zone->next;
			}
			return 1;
		}
		tmp = zone;
		zone = zone->next;
	}
	return 0;
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
	ft_printf("free(%p);\n", ptr);
	if (!ptr)
		return ;
	else if (find_ptr_in_list(g_mem.tiny, ptr))
		return ;
	else if (find_ptr_in_list(g_mem.small, ptr))
		return ;
	else
		free_ptr_in_big(&g_mem.big, ptr);
}
