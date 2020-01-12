#include "ft_malloc.h"
#include <stdio.h>

int main(void)
{
	for(int i = 1; i < 550; i++)
	{
		void *s = malloc(599443);
		if (!s)
		{
			printf("error\n");
			return 4;
		}
	}
	system("leaks test");
}
