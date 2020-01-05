/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybuhai <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/31 17:18:30 by ybuhai            #+#    #+#             */
/*   Updated: 2018/11/07 16:50:49 by ybuhai           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static size_t	helper(char const *s)
{
	size_t i;
	size_t j;

	i = 0;
	while (s[i] == ' ' || s[i] == '\n' || s[i] == '\t')
		i++;
	if (!s[i])
		return (0);
	j = 0;
	while (s[i++])
		j++;
	i -= 2;
	while (s[i] == ' ' || s[i] == '\n' || s[i] == '\t')
	{
		i--;
		j--;
	}
	return (j);
}

char			*ft_strtrim(char const *s)
{
	char	*res;
	size_t	i;
	size_t	j;

	if (!s)
		return (NULL);
	i = helper(s);
	if (!i)
		return (ft_strdup("\0"));
	j = 0;
	while (s[j] == ' ' || s[j] == '\n' || s[j] == '\t')
		j++;
	res = ft_strnew(i);
	if (!res)
		return (NULL);
	ft_strncpy(res, &s[j], i);
	return (res);
}
