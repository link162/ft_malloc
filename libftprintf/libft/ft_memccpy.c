/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memccpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybuhai <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/29 18:36:08 by ybuhai            #+#    #+#             */
/*   Updated: 2018/11/07 22:04:17 by ybuhai           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memccpy(void *d, const void *s, int c, size_t n)
{
	unsigned char	*ndest;
	unsigned char	*nsrc;
	size_t			i;

	ndest = (unsigned char *)d;
	nsrc = (unsigned char *)s;
	i = 0;
	while (i < n)
	{
		ndest[i] = nsrc[i];
		if (nsrc[i] == (unsigned char)c)
			return (d + i + 1);
		i++;
	}
	return (NULL);
}
