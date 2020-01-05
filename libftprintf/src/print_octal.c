/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_octal.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybuhai <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/08 19:10:07 by ybuhai            #+#    #+#             */
/*   Updated: 2019/01/16 12:55:52 by ybuhai           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ft_printf.h>

void		print_last_ptr(char *str, int nulls_before, int f)
{
	int			str_len;
	int			i;

	i = 0;
	str_len = ft_strlen(str);
	while ((g_flags.precision > -1 || g_flags.flag[3] != '0') && 0 < f--)
		ft_put_char(' ');
	while (i < 2)
		ft_put_char(str[i++]);
	i = 0;
	while (g_flags.flag[3] == '0' && f-- > 0)
		ft_put_char('0');
	while (i++ < nulls_before)
		ft_put_char('0');
	i = 2;
	while (i < str_len)
		ft_put_char(str[i++]);
}

static int	ft_octal(unsigned long long nbr, char *str)
{
	int		i;

	i = 0;
	if (nbr >= 8)
		i = ft_octal(nbr / 8, str);
	str[i] = (nbr % 8) + 48;
	return (1 + i);
}

static void	print_last_oct(char *str, int nulls_before, int free_place)
{
	while (free_place > 0 && ((g_flags.precision >= 0)
				|| (g_flags.precision == -1 && g_flags.flag[3] != '0')))
	{
		ft_put_char(' ');
		free_place--;
	}
	if (g_flags.flag[4] == '#' && (str[0] != '0' ||
				(str[0] == '0' && g_flags.precision == 0)))
		ft_put_char('0');
	if (g_flags.precision == 0 && str[0] == '0')
	{
		if (g_flags.width >= 0)
			ft_put_char(' ');
		return ;
	}
	while (free_place > 0 && g_flags.flag[3] == '0')
	{
		ft_put_char('0');
		free_place--;
	}
	while (nulls_before-- > 0)
		ft_put_char('0');
	while (*str)
		ft_put_char(*str++);
}

static void	print_first_oct(char *str, int nulls_before, int free_place)
{
	if (g_flags.flag[4] == '#' && str[0] != '0')
		ft_put_char('0');
	while (nulls_before-- > 0)
		ft_put_char('0');
	while (*str)
		ft_put_char(*str++);
	while (free_place-- > 0)
		ft_put_char(' ');
}

void		print_octal(unsigned long long nbr)
{
	int		int_len;
	int		free_place_before_nbr;
	int		nulls_before_nbr;
	char	str[25];

	ft_bzero(str, 25);
	ft_octal(nbr, str);
	int_len = ft_strlen(str);
	free_place_before_nbr = 0;
	nulls_before_nbr = 0;
	if (int_len <= g_flags.precision)
		nulls_before_nbr = g_flags.precision - int_len -
			(g_flags.flag[4] == '#' ? 1 : 0);
	if (int_len <= g_flags.width || g_flags.precision < g_flags.width)
		free_place_before_nbr = int_len >= g_flags.precision ?
			g_flags.width - int_len : g_flags.width - g_flags.precision;
	if (free_place_before_nbr > 0 && g_flags.flag[4] == '#' &&
			nbr != 0 && g_flags.precision == -1)
		free_place_before_nbr -= 1;
	if (g_flags.flag[0] == '-')
		print_first_oct(str, nulls_before_nbr, free_place_before_nbr);
	else
		print_last_oct(str, nulls_before_nbr, free_place_before_nbr);
}
