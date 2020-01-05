/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybuhai <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/29 18:39:57 by ybuhai            #+#    #+#             */
/*   Updated: 2018/11/07 22:10:15 by ybuhai           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *s, int ch)
{
	char		*str;
	long long	x;

	str = (char *)s;
	x = ft_strlen(str);
	while (x >= 0)
	{
		if (s[x] == ch)
			return (&str[x]);
		x--;
	}
	return (NULL);
}
