/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybuhai <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/29 17:04:13 by ybuhai            #+#    #+#             */
/*   Updated: 2018/11/07 22:11:13 by ybuhai           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int		ft_strcmp(const char *s1, const char *s2)
{
	int x;

	x = ((ft_strlen(s1) > ft_strlen(s2)) ? ft_strlen(s1) : ft_strlen(s2));
	return (ft_memcmp(s1, s2, x));
}
