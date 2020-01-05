/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybuhai <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/29 18:39:18 by ybuhai            #+#    #+#             */
/*   Updated: 2018/11/07 22:09:07 by ybuhai           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t size)
{
	char			*d;
	const char		*s;
	size_t			l;
	size_t			n;

	n = size;
	d = dst;
	s = src;
	while (*d && n--)
		d++;
	l = d - dst;
	n = size - l;
	if (n <= 0)
		return (l + ft_strlen((char *)s));
	while (*s)
	{
		if (n != 1)
		{
			*d++ = *s;
			n--;
		}
		s++;
	}
	*d = '\0';
	return (l + (s - src));
}
