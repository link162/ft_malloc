#include "ft_malloc.h"
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <errno.h>
#include <pthread.h>

void *foo(void *d)
{
	for(int i = 0; i < 1000; i++)
	{
		char *s1 = malloc(i);
		char *s2 = realloc(s1, i + 10);
		free(s2);
		s1 = malloc(i / 2);
		s2 = malloc(234);
		free(s1);
		free(s2);
		printf("%i %lli\n", i, pthread_self());
		show_alloc_mem_ex(void);
	}
	return NULL;
}

int main(int argc, char **argv)
{
	pthread_t t1;
	pthread_t t2;
	pthread_t t3;
	pthread_create(&t1, NULL, foo, NULL);
	pthread_create(&t2, NULL, foo, NULL);
	pthread_create(&t3, NULL, foo, NULL);
	pthread_join(t1, NULL);
	pthread_join(t2, NULL);
	pthread_join(t3, NULL);
}
