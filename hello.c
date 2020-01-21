#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

void foo()
{
	char *d;
	realloc(d, 10);
}

int main(void)
{
	char *d;
	realloc(d, 10);
	foo();
}
