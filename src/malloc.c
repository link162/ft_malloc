#include "ft_malloc_internal.h"

t_mem g_mem = {0};

void	*alloc_big_zone(size_t size)
{
	ft_printf("here\n");
	int page_size;
	t_zone *new;

	page_size = getpagesize();
	new = mmap(NULL, (size / page_size + 1) * page_size,
			PROT_READ | PROT_WRITE,
			MAP_ANONYMOUS | MAP_PRIVATE, -1, 0);
	if (new == MAP_FAILED)
		return NULL;
	ft_printf("end\n");
	new->next = g_mem.big;
	ft_printf("end1\n");
	new->size = (size / page_size + 1) * page_size - sizeof(t_zone);
	ft_printf("end2\n");
	new->used = 1;
	g_mem.big = new;
	return ((void *)((void *)new) + sizeof(t_zone));
}

int		mem_init()
{
	g_mem.tiny = (t_zone *)alloc_big_zone((TINY_SIZE + sizeof(t_zone)) *
			NUM_PRE_ALLOC + sizeof(t_zone));
	if (!g_mem.tiny)
		return (1);
	g_mem.tiny->size = (TINY_SIZE + sizeof(t_zone)) * NUM_PRE_ALLOC - sizeof(t_zone);
	g_mem.tiny->next = NULL;
	g_mem.tiny->used = 0;
	g_mem.small = (t_zone *)alloc_big_zone((SMALL_SIZE + sizeof(t_zone)) *
				NUM_PRE_ALLOC + sizeof(t_zone));
	if (!g_mem.small)
		return (1);
	g_mem.small->size = (SMALL_SIZE + sizeof(t_zone)) * NUM_PRE_ALLOC - sizeof(t_zone);
	g_mem.small->next = NULL;
	g_mem.small->used = 0;
	return (0);
}

void *find_memory(size_t size, t_zone *zone, int tiny)
{
	t_zone *last;

	while(zone)
	{
		if (!zone->used && zone->size >= size)
		{
			zone->used = 1;
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
	last->next = (t_zone *)alloc_big_zone((SMALL_SIZE + sizeof(t_zone)) * NUM_PRE_ALLOC + sizeof(t_zone));
	if (!last->next)
		return (NULL);
	last = last->next;
	last->size = size;
	last->used = 1;
	last->next = last + size + sizeof(t_zone);
	last->next->size = (TINY_SIZE + sizeof(t_zone)) * NUM_PRE_ALLOC - size - sizeof(t_zone) * 2;
	last->next->used = 0;
	last->next->next = NULL;
	return ((void *)(last + sizeof(t_zone)));
}


void *malloc(size_t size)
{
	ft_printf("malloc(%lli);\n");
	if (size < 0)
		return (NULL);
	if (!size)
		size = TINY_SIZE;
	if (!g_mem.tiny)
		if (mem_init())
			return (NULL);
	if (TINY_SIZE >= size)
		return (find_memory(size, g_mem.tiny, 1));
	else if(SMALL_SIZE >= size)
		return (find_memory(size, g_mem.small, 0));
	else
		return (alloc_big_zone(size + sizeof(t_zone)));
	return (NULL);
}
