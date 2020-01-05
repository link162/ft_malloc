/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybuhai <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/29 18:36:45 by ybuhai            #+#    #+#             */
/*   Updated: 2018/11/07 22:05:19 by ybuhai           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memchr(const void *str, int c, size_t n)
{
	void	*res;
	size_t	i;
	char	*s;

	s = (char *)str;
	res = (void *)str;
	i = 0;
	while (i < n)
	{
		if (s[i] == (char)c)
			return (res + i);
		i++;
	}
	return (NULL);
}
