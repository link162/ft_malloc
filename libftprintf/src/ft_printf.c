/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybuhai <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/11 11:38:09 by ybuhai            #+#    #+#             */
/*   Updated: 2019/01/16 13:58:36 by ybuhai           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ft_printf.h>

void		ft_put_char(int c)
{
	int i;

	g_count++;
	i = write(1, &c, 1);
	i++;
}

static int	check_flags(char c)
{
	if (c == '-' || c == '+' || c == ' ' || c == '#' || c == '0')
	{
		if (c == '-')
			g_flags.flag[0] = c;
		else if (c == '+')
			g_flags.flag[1] = c;
		else if (c == ' ')
			g_flags.flag[2] = c;
		else if (c == '0')
			g_flags.flag[3] = c;
		else if (c == '#')
			g_flags.flag[4] = c;
		return (1);
	}
	return (0);
}

static int	check_specified(const char *str, va_list argptr)
{
	int i;
	int tmp;

	struct_to_nul();
	i = 1;
	while (check_flags(str[i]))
		i++;
	if (!str[i])
		return (i - 1);
	tmp = check_width(&str[i]);
	if (tmp == -1)
		return (-1);
	i += tmp;
	tmp = check_precision(&str[i]);
	if (tmp == -1)
		return (-1);
	i += tmp;
	while (check_length(&str[i], &i))
		i++;
	while (check_flags(str[i]))
		i++;
	if (!(check_symbol(str[i])))
		return (i - 1);
	prepare_to_print(argptr);
	return (i);
}

int			ft_printf(const char *format, ...)
{
	va_list argptr;
	int		i;
	int		tmp;

	g_count = 0;
	i = 0;
	va_start(argptr, format);
	while (format[i])
	{
		if (format[i] == '%')
		{
			tmp = check_specified(&format[i], argptr);
			if (tmp == -1)
				return (-1);
			i += tmp;
		}
		else
			ft_put_char(format[i]);
		i++;
	}
	va_end(argptr);
	return (g_count);
}

int			ft_getdouble_len(long double value, long double *limit)
{
	unsigned int	len;

	len = 2;
	*limit = 1;
	if (value < 0)
		len++;
	while (value > 10 || value < -10)
	{
		len++;
		value = value / 10;
		*limit = (*limit) * 10;
	}
	return (len);
}
