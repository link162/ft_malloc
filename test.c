//#include "ft_malloc.h"
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <errno.h>
#include <pthread.h>

int main(int argc, char **argv)
{
	printf("%p\n", malloc(943825029350483925));
}
