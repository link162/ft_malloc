/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybuhai <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/29 18:34:34 by ybuhai            #+#    #+#             */
/*   Updated: 2018/11/07 22:04:12 by ybuhai           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memcpy(void *dest, const void *src, size_t n)
{
	char		*ndest;
	const char	*nsrc;
	size_t		i;

	ndest = dest;
	nsrc = src;
	i = 0;
	while (i < n)
	{
		*(ndest + i) = *(nsrc + i);
		i++;
	}
	return (dest);
}
