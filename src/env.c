/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybuhai <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/26 21:03:42 by ybuhai            #+#    #+#             */
/*   Updated: 2020/01/27 20:48:58 by ybuhai           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_malloc_internal.h"
#define GET_ENV extern char **environ

GET_ENV;

int		is_global_var_set(void)
{
	char	**env;

	env = environ;
	while (*env)
	{
		if (!ft_strncmp(*env, "MallocStackLogging", 18))
			return (1);
		env++;
	}
	return (0);
}

size_t	print_zone(t_zone *zone)
{
	size_t i;

	i = 0;
	while (zone)
	{
		if (zone->used == FOR_MEM)
		{
			ft_printf("%p - %p : %llu bytes\n", zone + 1, (void *)(zone + 1)
					+ zone->size, zone->size);
			i += zone->size;
		}
		zone = zone->next;
	}
	return (i);
}

void	show_alloc_mem(void)
{
	size_t i;

	pthread_mutex_lock(&g_mutex);
	ft_printf("TINY : %p\n", g_mem.tiny);
	i = print_zone(g_mem.tiny);
	ft_printf("SMALL : %p\n", g_mem.tiny);
	i += print_zone(g_mem.small);
	ft_printf("LARGE : %p\n", g_mem.tiny);
	i += print_zone(g_mem.big);
	ft_printf("Total : %llu bytes\n", i);
	pthread_mutex_unlock(&g_mutex);
}
