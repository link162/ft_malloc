/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strsplit.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybuhai <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/01 13:41:48 by ybuhai            #+#    #+#             */
/*   Updated: 2018/11/07 17:36:18 by ybuhai           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int		ft_count_words(char const *s, char c)
{
	unsigned int	i;
	int				count;

	i = 0;
	count = 0;
	while (*s)
	{
		if (i == 1 && *s == c)
			i = 0;
		if (i == 0 && *s != c)
		{
			i = 1;
			count++;
		}
		s++;
	}
	return (count);
}

static int		ft_modstrlen(char const *str, char c)
{
	int i;

	i = 0;
	while (str[i] != c && str[i] != '\0')
		i++;
	i++;
	return (i);
}

static char		*ft_copy(char **des, char const *str, char c)
{
	int i;

	*des = (char *)malloc(sizeof(char) * (ft_modstrlen(str, c)));
	if (!des)
		return (NULL);
	i = 0;
	while (str[i] != c && str[i] != '\0')
	{
		(*des)[i] = str[i];
		i++;
	}
	(*des)[i] = '\0';
	return (*des);
}

char			**ft_strsplit(char const *s, char c)
{
	char	**res;
	int		i;
	int		j;

	j = 0;
	i = 0;
	if (!s)
		return (NULL);
	if (!(res = (char **)malloc(sizeof(char *) * (ft_count_words(s, c) + 1))))
		return (NULL);
	while (s[i])
	{
		while (s[i] == c && s[i])
			i++;
		if (s[i])
		{
			if (!(ft_copy(&res[j], &s[i], c)))
				return (NULL);
			j++;
		}
		while (s[i] != c && s[i])
			i++;
	}
	res[j] = NULL;
	return (res);
}
