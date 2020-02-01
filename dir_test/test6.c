/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybuhai <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/25 13:57:33 by ybuhai            #+#    #+#             */
/*   Updated: 2020/01/27 20:59:29 by ybuhai           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <errno.h>
#include <pthread.h>

int		main(int argc, char **argv)
{
	char	*str;
	int		i;

	str = calloc(sizeof(char), 50);
	while (i < 50)
	{
		printf("%i", str[i]);
		i++;
	}
	printf("\n");
}
