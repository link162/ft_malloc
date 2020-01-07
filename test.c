#include "malloc.h"

int main(void)
{
	say_hello();
	char *tmp = malloc(5);

	char *str = strdup("hello world\n");
	ft_printf(str);
}
