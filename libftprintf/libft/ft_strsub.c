/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strsub.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybuhai <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/30 15:29:51 by ybuhai            #+#    #+#             */
/*   Updated: 2018/10/30 18:22:39 by ybuhai           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strsub(char const *s, unsigned int start, size_t len)
{
	char	*res;

	if (!s)
		return (NULL);
	res = (char *)malloc(sizeof(*s) * (len + 1));
	if (!res)
		return (NULL);
	ft_strncpy(res, &s[start], len);
	res[len] = '\0';
	return (res);
}
