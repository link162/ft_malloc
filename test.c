//#include "ft_malloc.h"
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <errno.h>
#include <pthread.h>

int main(int argc, char **argv)
{
	for(int i = 0; i < 98; i++)
		malloc(128);
	char *s99 = malloc(128);
	char *s100 = malloc(128);
	char *s1 = malloc(128);
	char *s2 = malloc(128);
	//free(s2);
	free(s1);
	count_tiny();
	/*
	char *s2 = malloc(128);
	free(s99);
	free(s100);
	*/
}
