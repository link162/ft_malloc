/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybuhai <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/29 18:38:22 by ybuhai            #+#    #+#             */
/*   Updated: 2018/11/07 22:07:06 by ybuhai           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strncpy(char *dest, const char *src, size_t n)
{
	size_t i;

	i = 0;
	while (i < n)
	{
		if (*(src + i))
			*(dest + i) = *(src + i);
		else
			while (i < n)
				dest[i++] = '\0';
		i++;
	}
	return (dest);
}
