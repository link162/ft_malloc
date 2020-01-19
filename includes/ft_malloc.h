/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   malloc.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybuhai <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/05 12:29:52 by ybuhai            #+#    #+#             */
/*   Updated: 2020/01/19 02:37:32 by ybuhai           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_MALLOC_H
# define FT_MALLOC_H
# include <sys/types.h>
# include <stdlib.h>

void *malloc(size_t size);
void *realloc(void *ptr, size_t size);
void free(void *ptr);
void show_alloc_mem_ex(void);
void malloc_show_history(void);

#endif
