#include "malloc.h"

void *malloc(size_t n)
{
	printf("Called malloc, size %zu\n", n);
	return NULL;
}
