/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybuhai <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/25 13:57:33 by ybuhai            #+#    #+#             */
/*   Updated: 2020/01/25 19:27:27 by ybuhai           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <errno.h>
#include <pthread.h>

void	*foo(void *d)
{
	char	*s1;
	char	*s2;
	int		i;

	i = 0;
	while (i < 1000)
	{
		s1 = malloc(i);
		s2 = realloc(s1, i + 10);
		free(s2);
		s1 = malloc(i / 2);
		s2 = malloc(234);
		free(s1);
		free(s2);
		i++;
	}
	return (NULL);
}

int		main(int argc, char **argv)
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
