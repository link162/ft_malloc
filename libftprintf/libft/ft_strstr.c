/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strstr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybuhai <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/29 15:40:12 by ybuhai            #+#    #+#             */
/*   Updated: 2018/11/07 22:10:32 by ybuhai           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strstr(const char *s1, const char *s2)
{
	int i;
	int pos;

	if (!*s2)
		return ((char *)s1);
	pos = 0;
	while (s1[pos])
	{
		if (s1[pos] == s2[0])
		{
			i = 1;
			while (s1[pos + i] == s2[i] && s1[pos + i] != '\0' && s2[i] != '\0')
				i++;
			if (s2[i] == '\0')
				return ((char *)&s1[pos]);
		}
		pos++;
	}
	return (NULL);
}
