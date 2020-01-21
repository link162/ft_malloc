#include "ft_malloc_internal.h"
#include <stdlib.h>

int main()
{
	void *t;
	t = malloc(1024);
	t = malloc(1024 * 32);
	t = malloc(1024 * 1024);
	t = malloc(1024 * 1024 * 16);
	t = malloc(1024 * 1024 * 128);
//	show_alloc_mem();
	return (0);
}
