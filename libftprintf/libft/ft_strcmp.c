/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybuhai <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/29 17:04:13 by ybuhai            #+#    #+#             */
/*   Updated: 2020/01/19 01:31:53 by ybuhai           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int		ft_strcmp(const char *s1, const char *s2)
{
	int x;

	if (!s1 || !s2)
		return (1);
	x = ((ft_strlen(s1) > ft_strlen(s2)) ? ft_strlen(s1) : ft_strlen(s2));
	return (ft_memcmp(s1, s2, x));
}
