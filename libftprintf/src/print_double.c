/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_double.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybuhai <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/27 17:17:11 by ybuhai            #+#    #+#             */
/*   Updated: 2019/01/08 19:38:12 by ybuhai           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ft_printf.h>

void				helper(char *res, long double nbr, int len, long double li)
{
	int				i;
	int				t;
	int				l;
	int				f;

	f = 1;
	l = -1;
	l = g_flags.precision >= 0 ? (unsigned int)g_flags.precision : 6;
	i = 0;
	if (nbr < 0.0)
	{
		f = -1;
		res[0] = '-';
		i++;
	}
	while (i < len + l)
	{
		if (i == len - 1)
			i++;
		t = get_float_bit(f * nbr, li);
		res[i] = t + '0';
		nbr = nbr - f * li * t;
		li = li / 10;
		i++;
	}
}

static char			*ftoi(long double nbr)
{
	int				len;
	long double		limit;
	char			*res;
	int				l;

	l = g_flags.precision >= 0 ? (unsigned int)g_flags.precision : 6;
	if (g_flags.precision == 0)
		l = -1;
	len = ft_getdouble_len(nbr, &limit);
	res = ft_strnew(len + l + 1);
	if (g_flags.precision != 0)
		res[len - 1] = '.';
	helper(res, nbr, len, limit);
	return (res);
}

static void			print_first_double(long double nbr, char *str, int nbr_len)
{
	int				i;

	i = 0;
	if (nbr >= 0 && g_flags.flag[1] == '+')
	{
		ft_put_char('+');
		g_flags.width--;
	}
	else if (nbr >= 0 && g_flags.flag[2] == ' ')
	{
		ft_put_char(' ');
		g_flags.width--;
	}
	while (str[i])
		ft_put_char(str[i++]);
	i = g_flags.width - nbr_len;
	while (i-- > 0)
		ft_put_char(' ');
}

static void			print_last_d(long double nbr, char *str, int len, int i)
{
	if (g_flags.flag[3] == '0' && nbr >= 0)
	{
		if (g_flags.flag[1] == '+')
			ft_put_char('+');
		else if (g_flags.flag[2] == ' ')
			ft_put_char(' ');
	}
	while (g_flags.width - len > 0)
	{
		if (g_flags.flag[3] == '0')
			ft_put_char('0');
		else
			ft_put_char(' ');
		g_flags.width--;
	}
	if (g_flags.flag[3] != '0' && nbr >= 0)
	{
		if (g_flags.flag[1] == '+')
			ft_put_char('+');
		else if (g_flags.flag[2] == ' ')
			ft_put_char(' ');
	}
	while (str[i])
		ft_put_char(str[i++]);
}

void				print_double(long double nbr)
{
	char			*str;
	int				nbr_len;
	int				i;

	i = 0;
	nbr = round_off(nbr);
	str = ftoi(nbr);
	nbr_len = ft_strlen(str);
	if ((g_flags.flag[1] == '+' || g_flags.flag[2] == ' ') && nbr >= 0)
		g_flags.width--;
	if (g_flags.flag[0] == '-')
		print_first_double(nbr, str, nbr_len);
	else
	{
		if (str[i] == '-' && g_flags.flag[3] == '0')
			ft_put_char(str[i++]);
		print_last_d(nbr, str, nbr_len, i);
	}
	free(str);
}
