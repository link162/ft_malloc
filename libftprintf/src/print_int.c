/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_int.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybuhai <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/08 19:17:21 by ybuhai            #+#    #+#             */
/*   Updated: 2019/01/15 12:21:30 by ybuhai           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ft_printf.h>

static void	ft_put_nbr(__int128 x)
{
	if (x < 0)
	{
		ft_put_char('-');
		x *= -1;
	}
	if (x > 9)
	{
		ft_put_nbr(x / 10);
		ft_put_nbr(x % 10);
	}
	if (x < 10)
		ft_put_char(x + 48);
}

static void	print_first_nbr(__int128 nbr, int nulls_before, int free_place)
{
	int		i;

	if (g_flags.flag[1] == '+' && nbr >= 0)
	{
		ft_put_char('+');
		free_place--;
	}
	else if (g_flags.flag[2] == ' ' && nbr >= 0)
	{
		ft_put_char(' ');
		free_place--;
	}
	else if (nbr < 0)
	{
		ft_put_char('-');
		nbr *= -1;
	}
	i = 0;
	while (i++ < nulls_before)
		ft_put_char('0');
	ft_put_nbr(nbr);
	i = 0;
	while (i++ < free_place)
		ft_put_char(' ');
}

static void	finish_nbr(__int128 nbr, int nulls_before, int fp)
{
	int i;

	i = 0;
	while (i++ < fp)
		if (g_flags.flag[3] == '0')
			ft_put_char('0');
		else
			ft_put_char(' ');
	i = 0;
	if (nbr >= 0 && g_flags.flag[1] == '+' && g_flags.flag[3] != '0' &&
			g_flags.symbol != 'u')
		ft_put_char('+');
	if (nbr < 0)
	{
		ft_put_char('-');
		nbr *= -1;
	}
	while (i++ < nulls_before)
		ft_put_char('0');
	ft_put_nbr(nbr);
}

static void	print_last_nbr(__int128 nbr, int nulls_before, int fp)
{
	if ((g_flags.flag[1] == '+' || g_flags.flag[2] == ' ') && nbr >= 0)
		fp--;
	if (g_flags.flag[1] == '+' && nbr >= 0 && g_flags.flag[3] == '0' &&
			g_flags.symbol != 'u')
		ft_put_char('+');
	else if (g_flags.flag[2] == ' ' && nbr >= 0 && g_flags.flag[1] != '+'
			&& g_flags.symbol != 'u')
		ft_put_char(' ');
	else if (nbr < 0 && nulls_before >= 0 && g_flags.flag[3] == '0')
	{
		ft_put_char('-');
		nbr *= -1;
	}
	finish_nbr(nbr, nulls_before, fp);
}

void		print_int(__int128 nbr)
{
	int		int_len;
	int		nulls_before_nbr;
	int		free_place_before_nbr;

	free_place_before_nbr = 0;
	nulls_before_nbr = 0;
	int_len = nbr < 0 ? intlen(nbr) - 1 : intlen(nbr);
	if (nbr == 0 && g_flags.precision == 0)
	{
		while (g_flags.width-- > 0)
			ft_put_char(' ');
		return ;
	}
	if (g_flags.precision >= 0)
		g_flags.flag[3] = 0;
	if (int_len < g_flags.precision)
		nulls_before_nbr = g_flags.precision - int_len;
	if (int_len + (nbr < 0 ? 1 : 0) + nulls_before_nbr < g_flags.width)
		free_place_before_nbr = g_flags.width - int_len - (nbr < 0 ? 1 : 0)
			- nulls_before_nbr;
	if (g_flags.flag[0] == '-')
		print_first_nbr(nbr, nulls_before_nbr, free_place_before_nbr);
	else
		print_last_nbr(nbr, nulls_before_nbr, free_place_before_nbr);
}
