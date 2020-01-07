#include "malloc.h"
void *malloc(size_t n);
void say_hello(void);

int main(void)
{
	say_hello();
	char *tmp = malloc(5);

	char *str = strdup("hello world\n");
	ft_printf(str);
}
