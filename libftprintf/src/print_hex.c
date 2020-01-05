/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_hex.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybuhai <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/08 19:20:07 by ybuhai            #+#    #+#             */
/*   Updated: 2019/01/15 15:37:51 by ybuhai           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ft_printf.h>

int			ft_a_toi(const char *str)
{
	__int128	res;
	int			i;
	int			m;

	i = 0;
	res = 0;
	m = 1;
	while (str[i] == '-')
		i++;
	if (i > 0)
		m = -1;
	while (ft_isdigit(str[i]))
		res = (res * 10) + (str[i++] - '0');
	res *= m;
	if (res > 2147483647 || res < -2147483648)
		return (-2147483648);
	return ((int)res);
}

static int	print_16(char *str, __int128 nbr)
{
	int		i;

	i = 0;
	if (nbr >= 16)
		i = print_16(str, nbr / 16);
	if (nbr % 16 < 10)
	{
		str[i] = (nbr % 16) + 48;
		return (1 + i);
	}
	else
	{
		if (g_flags.symbol == 'X')
			str[i] = nbr % 16 + 55;
		else
			str[i] = nbr % 16 + 87;
		return (1 + i);
	}
}

static void	print_last_hex(char *str, int nulls_before, int free_place)
{
	if (g_flags.precision == 0 && str[0] == '0')
	{
		if (g_flags.width >= 0)
			ft_put_char(' ');
		return ;
	}
	if (g_flags.flag[4] == '#' && str[0] != '0')
	{
		ft_put_char('0');
		if (g_flags.symbol == 'x')
			ft_put_char('x');
		else
			ft_put_char('X');
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

static void	print_first_hex(char *str, int nulls_before, int free_place)
{
	if (g_flags.flag[4] == '#' && str[0] != '0')
	{
		ft_put_char('0');
		if (g_flags.symbol == 'x')
			ft_put_char('x');
		else
			ft_put_char('X');
	}
	while (nulls_before-- > 0)
		ft_put_char('0');
	while (*str)
		ft_put_char(*str++);
	while (free_place-- > 0)
		ft_put_char(' ');
}

void		print_hex(__int128 nbr, int f)
{
	char	str[25];
	int		i;
	int		n;

	ft_bzero(str, 25);
	print_16(str, nbr);
	i = ft_strlen(str);
	n = g_flags.precision >= 0 ? g_flags.precision - i : 0;
	if (i <= g_flags.width || g_flags.precision < g_flags.width)
		f = i >= g_flags.precision ? g_flags.width - i :
			g_flags.width - g_flags.precision;
	if (f > 0 && g_flags.flag[4] == '#' && nbr != 0)
		f -= 2;
	if (g_flags.flag[0] == '-')
		print_first_hex(str, n, f);
	else
	{
		while (f > 0 && ((g_flags.precision >= 0)
					|| (g_flags.precision == -1 && g_flags.flag[3] != '0')))
		{
			ft_put_char(' ');
			f--;
		}
		print_last_hex(str, n, f);
	}
}
