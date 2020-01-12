#include "ft_malloc_internal.h"

void do_work()
{
	printf("do_work thread %lli\n", (long long)pthread_self());
	for(int i = 20; i < 30; i++)
	{
		void * t = malloc(i);
//		sleep(1);
	}
}

int main(void)
{
	printf("page size %i\n", getpagesize());
	pthread_t curr;
	int res = pthread_create(&curr, NULL, (void *)do_work, NULL);
	printf("main thread %lli\n", (long long)pthread_self());
	for(int i = 0; i < 10; i++)
	{
		void * t = malloc(-5);
	}
	pthread_join(curr, NULL);
	
}
