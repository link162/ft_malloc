/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   malloc.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybuhai <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/05 12:29:52 by ybuhai            #+#    #+#             */
/*   Updated: 2020/01/27 20:57:21 by ybuhai           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_MALLOC_INTERNAL_H
# define FT_MALLOC_INTERNAL_H
# include "libftprintf.h"
# include <pthread.h>
# include <sys/mman.h>

# define NUM_PRE_ALLOC 1000
# define TINY_SIZE 128
# define SMALL_SIZE 1024
# define FOR_POOL 2
# define FOR_MEM 1

typedef enum
{
	F_MALLOC,
	F_REALLOC,
	F_FREE
}	t_func;

typedef struct		s_zone
{
	size_t			size;
	int				used;
	struct s_zone	*next;
}					t_zone;

typedef struct		s_hist
{
	size_t			size;
	t_func			func;
	struct s_hist	*next;
}					t_hist;

typedef struct		s_mem
{
	t_zone			*tiny;
	t_zone			*small;
	t_zone			*big;
	t_hist			*hist;
}					t_mem;

extern t_mem		g_mem;
extern pthread_mutex_t	g_mutex;

void				*calloc(size_t count, size_t size);
void				*malloc(size_t size);
void				free(void *ptr);
void				*realloc(void *ptr, size_t size);
void				show_alloc_mem(void);
void				show_alloc_mem_ex(void);
void				write_history(t_func func, size_t size);
int					is_global_var_set(void);
void				*find_memory(size_t size, t_zone *zone, int tiny, int f);
int					mem_init(void);

#endif
