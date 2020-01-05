/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybuhai <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/29 18:13:22 by ybuhai            #+#    #+#             */
/*   Updated: 2018/11/07 22:11:33 by ybuhai           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int		ft_strncmp(const char *s, const char *s2, size_t n)
{
	size_t i;

	i = 0;
	while (s[i] != '\0' && (unsigned char)s[i] == (unsigned char)s2[i] && i < n)
		i++;
	if (i == n)
		return (0);
	return ((unsigned char)s[i] - (unsigned char)s2[i]);
}
