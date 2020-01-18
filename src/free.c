#include "ft_malloc_internal.h"

void count_tiny(void)
{
	t_zone *tmp = g_mem.tiny;
	int i = 0;
	while(tmp)
	{
		i++;
		tmp = tmp->next;
	}
	//ft_printf("number %i\n", i);
	
}

int		 find_ptr_in_list(t_zone *zone, void *ptr)
{
	t_zone *tmp;

	tmp = NULL;
	while(zone)
	{
		if (zone + 1 == ptr)
		{
	//ft_printf("free zone\n");
			zone->used = 0;
			if (zone->next && !zone->next->used && zone->next == (void *)zone + zone->size + sizeof(t_zone))
			{
	//ft_printf("combine with next\n");
				zone->size += zone->next->size + sizeof(t_zone);
				zone->next = zone->next->next;
			}
			if (tmp && !tmp->used && (void *)tmp + tmp->size + sizeof(t_zone) == zone)
			{
	//ft_printf("combine with prev\n");
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
	//ft_printf("free(%p);\n", ptr);
	if (!ptr)
		return ;
	else if (find_ptr_in_list(g_mem.tiny, ptr))
		return ;
	else if (find_ptr_in_list(g_mem.small, ptr))
		return ;
	else
		free_ptr_in_big(&g_mem.big, ptr);
}
