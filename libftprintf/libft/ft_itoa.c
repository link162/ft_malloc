/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybuhai <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/01 17:01:08 by ybuhai            #+#    #+#             */
/*   Updated: 2018/11/06 14:49:38 by ybuhai           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	count_ch(int n)
{
	int	j;

	j = 2;
	if (n < 0)
		j++;
	while (n /= 10)
		j++;
	return (j);
}

char		*ft_itoa(int n)
{
	int		i;
	char	*str;

	i = count_ch(n);
	str = (char *)malloc(sizeof(char) * i);
	if (!str)
		return (NULL);
	ft_bzero(str, i);
	i -= 2;
	if (!str)
		return (NULL);
	if (n < 0)
		str[0] = '-';
	if (n == 0)
		str[0] = '0';
	while (n)
	{
		if (n > 0)
			str[i] = (n % 10) + 48;
		else
			str[i] = -(n % 10) + 48;
		i--;
		n = n / 10;
	}
	return (str);
}
