/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test5.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybuhai <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/25 14:44:04 by ybuhai            #+#    #+#             */
/*   Updated: 2020/01/27 20:58:37 by ybuhai           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ft_malloc_internal.h>

int	main(void)
{
	void *t;

	t = malloc(1024);
	t = malloc(1024 * 32);
	t = malloc(1024 * 1024);
	t = malloc(1024 * 1024 * 16);
	t = malloc(1024 * 1024 * 128);
	show_alloc_mem_ex();
	return (0);
}
