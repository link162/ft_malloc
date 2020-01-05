/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybuhai <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/28 09:13:35 by ybuhai            #+#    #+#             */
/*   Updated: 2019/01/16 13:45:31 by ybuhai           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ft_printf.h>

static char	hex_digit(int v)
{
	if (v >= 0 && v < 10)
		return ('0' + v);
	else
		return ('a' + v - 10);
}

void		print_address_hex(void *p0)
{
	int			i;
	int			counter;
	intptr_t	p;
	char		str[255];

	p = (intptr_t)p0;
	fill_str(str, &counter);
	if (p != 0)
	{
		i = (sizeof(p) << 3) - 4;
		while (i >= 0)
		{
			if (counter == 1)
			{
				while (hex_digit((p >> i) & 0xf) == '0')
					i -= 4;
				counter = 2;
			}
			str[counter++] = hex_digit((p >> i) & 0xf);
			i -= 4;
		}
	}
	if (g_flags.precision == 0)
		str[2] = '\0';
	print_ptr(str);
}

int			check_length(const char *str, int *i)
{
	if (str[0] == 'h')
	{
		if (str[1] == 'h')
			g_flags.length = 2;
		else
			g_flags.length = 1;
	}
	else if (str[0] == 'l')
	{
		if (str[1] == 'l')
			g_flags.length = 4;
		else
			g_flags.length = 3;
	}
	else if (str[0] == 'L')
		g_flags.length = 5;
	else
		return (0);
	if (g_flags.length == 2 || g_flags.length == 4)
		(*i)++;
	return (1);
}

void		print_first_ptr(char *str, int nulls_before, int free_place)
{
	int			str_len;
	int			i;

	str_len = ft_strlen(str);
	i = 0;
	while (i < 2)
		ft_put_char(str[i++]);
	i = 0;
	while (i++ < nulls_before)
		ft_put_char('0');
	i = 2;
	while (i < str_len)
		ft_put_char(str[i++]);
	while (free_place--)
		ft_put_char(' ');
}

int			check_symbol(char c)
{
	if (c == 'd' || c == 'i' || c == 's' || c == 'c' || c == 'f' || c == 'u' ||
			c == 'o' || c == 'x' || c == 'X' || c == 'p' || c == '%')
		g_flags.symbol = c;
	else
		return (0);
	return (1);
}
