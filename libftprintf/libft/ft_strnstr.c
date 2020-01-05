/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybuhai <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/29 16:26:37 by ybuhai            #+#    #+#             */
/*   Updated: 2018/11/07 22:10:43 by ybuhai           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *s1, const char *s2, size_t n)
{
	int i;
	int p;
	int r;
	int s;

	if (!*s2)
		return ((char *)s1);
	p = 0;
	r = 0;
	while (s1[p] && r < (int)n)
	{
		if (s1[p] == s2[0])
		{
			s = r + 1;
			i = 1;
			while (s1[p + i] == s2[i] && s1[p + i] != '\0' && s++ < (int)n)
				i++;
			if (s2[i] == '\0')
				return ((char *)&s1[p]);
		}
		p++;
		r++;
	}
	return (NULL);
}
