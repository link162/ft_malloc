/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_char.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybuhai <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/18 12:04:35 by ybuhai            #+#    #+#             */
/*   Updated: 2019/01/16 13:50:23 by ybuhai           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ft_printf.h>

void			print_ptr(char *str)
{
	int			str_len;
	int			free_place;
	int			nulls_before;
	int			z;

	z = 0;
	if (!str)
	{
		str = ft_strdup("(null)");
		z = 1;
	}
	free_place = 0;
	nulls_before = 0;
	str_len = ft_strlen(str);
	if (g_flags.precision > str_len - 2)
		nulls_before = g_flags.precision - str_len + 2;
	if (g_flags.width > str_len || g_flags.width > g_flags.precision + 2)
		free_place = str_len > g_flags.precision + 2 ?
			g_flags.width - str_len : g_flags.width - g_flags.precision - 2;
	if (g_flags.flag[0] == '-')
		print_first_ptr(str, nulls_before, free_place);
	else
		print_last_ptr(str, nulls_before, free_place);
	if (z)
		free(str);
}

void			print_char(int nbr)
{
	int			free_place;
	int			i;

	i = 0;
	free_place = 0;
	if (g_flags.width > 1)
		free_place = g_flags.width - 1;
	if (g_flags.flag[0] == '-')
	{
		ft_put_char(nbr);
		while (i++ < free_place)
			ft_put_char(' ');
	}
	else
	{
		while (i++ < free_place)
		{
			if (g_flags.flag[3] == '0')
				ft_put_char('0');
			else
				ft_put_char(' ');
		}
		ft_put_char(nbr);
	}
}

void			print_first_last(char *str, int lenght, int free_place)
{
	int			i;

	i = 0;
	if (g_flags.flag[0] == '-')
	{
		while (i < lenght)
			ft_put_char(str[i++]);
		while (free_place-- > 0)
			ft_put_char(' ');
	}
	else
	{
		while (free_place-- > 0)
		{
			if (g_flags.flag[3] == '0')
				ft_put_char('0');
			else
				ft_put_char(' ');
		}
		while (i < lenght)
			ft_put_char(str[i++]);
	}
}

void			print_str(char *str)
{
	int			str_len;
	int			free_place;
	int			lenght;
	int			z;

	z = 0;
	if (!str)
	{
		str = ft_strdup("(null)");
		z = 1;
	}
	free_place = 0;
	str_len = ft_strlen(str);
	lenght = str_len;
	if (g_flags.precision >= 0 && g_flags.precision < str_len)
		lenght = g_flags.precision;
	if ((g_flags.precision >= 0 && g_flags.precision > str_len && str_len <
				g_flags.width) || g_flags.precision < 0)
		free_place = g_flags.width - str_len;
	else if (g_flags.precision >= 0 && g_flags.precision < str_len &&
			g_flags.precision < g_flags.width)
		free_place = g_flags.width - g_flags.precision;
	print_first_last(str, lenght, free_place);
	if (z)
		free(str);
}
