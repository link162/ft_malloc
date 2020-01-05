/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybuhai <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/29 18:39:38 by ybuhai            #+#    #+#             */
/*   Updated: 2018/11/07 22:09:52 by ybuhai           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strchr(const char *str, int ch)
{
	size_t	i;
	char	*s;

	i = 0;
	s = (char *)str;
	while (s[i])
	{
		if (s[i] == (char)ch)
			return (&s[i]);
		i++;
	}
	if (s[i] == (char)ch)
		return (&s[i]);
	return (NULL);
}
