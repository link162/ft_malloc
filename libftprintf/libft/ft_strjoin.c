/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybuhai <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/30 16:37:24 by ybuhai            #+#    #+#             */
/*   Updated: 2018/10/30 18:18:12 by ybuhai           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	size_t	n;
	char	*str;

	if (!s1 || !s2)
		return (NULL);
	n = ft_strlen(s1) + ft_strlen(s2) + 1;
	str = (char *)malloc(sizeof(*s1) * n);
	if (!str)
		return (NULL);
	ft_strcpy(str, s1);
	ft_strcat(str, s2);
	return (str);
}
