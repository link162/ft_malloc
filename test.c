#include "ft_malloc.h"
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <errno.h>
#include <pthread.h>

int main(int argc, char **argv)
{
	
	free(NULL);
	free(NULL);
	realloc(NULL, 3);
	realloc(NULL, 3);
	char *s1 =	malloc(128);
	free(s1);
	show_alloc_mem_ex();
	malloc_show_history();
	/*
	s1 = malloc(128);
	free(s1);
	realloc(NULL, 3);
	realloc(NULL, 5);
*/
}
