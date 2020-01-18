/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   malloc.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybuhai <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/05 12:29:52 by ybuhai            #+#    #+#             */
/*   Updated: 2020/01/18 20:56:31 by ybuhai           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_MALLOC_INTER
#define FT_MALLOC_INTER
#include "libftprintf.h"
#include <pthread.h>
#include <sys/mman.h>

#define NUM_PRE_ALLOC 100
#define TINY_SIZE 128
#define SMALL_SIZE 512

typedef struct		s_zone
{
	size_t			size;
	int				used;
	struct s_zone	*next;
}					t_zone;

typedef struct		s_mem
{
	t_zone			*tiny;
	t_zone			*small;
	t_zone			*big;
}					t_mem;

extern t_mem		g_mem;
extern pthread_mutex_t	mutex;

void				*malloc(size_t size);
void				free(void *ptr);
void				*realloc(void *ptr, size_t size);
void				count_tiny();
#endif
