/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prepare_to_print.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybuhai <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/28 09:18:12 by ybuhai            #+#    #+#             */
/*   Updated: 2019/01/16 13:45:57 by ybuhai           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ft_printf.h>

void		fill_str(char *str, int *i)
{
	*i = 1;
	ft_bzero(str, 255);
	str[0] = '0';
	str[1] = 'x';
	str[2] = '0';
}

long double	round_off(long double nbr)
{
	long double		f;
	int				n;

	if (g_flags.precision >= 0)
	{
		f = 0.5;
		n = 0;
		while (n++ < g_flags.precision)
			f /= 10;
		if (nbr > 0)
			nbr += f;
		else if (nbr < 0)
			nbr -= f;
	}
	else
	{
		if (nbr < 0)
			nbr -= 0.0000005;
		else if (nbr > 0)
			nbr += 0.0000005;
	}
	return (nbr);
}

static void	prepare_to_print3(va_list argptr)
{
	if (g_flags.symbol == 'u' && g_flags.length == 0)
		print_int(va_arg(argptr, unsigned int));
	else if (g_flags.symbol == 'u' && g_flags.length == 2)
		print_int((unsigned char)va_arg(argptr, int));
	else if (g_flags.symbol == 'u' && g_flags.length == 1)
		print_int((unsigned short)va_arg(argptr, int));
	else if (g_flags.symbol == 'u' && g_flags.length == 3)
		print_int(va_arg(argptr, unsigned long));
	else if (g_flags.symbol == 'u' && g_flags.length == 4)
		print_int(va_arg(argptr, unsigned long long));
	else if (g_flags.symbol == 'f' && g_flags.length == 0)
		print_double(va_arg(argptr, double));
	else if (g_flags.symbol == 'f' && g_flags.length == 3)
		print_double(va_arg(argptr, double));
	else if (g_flags.symbol == 'f' && g_flags.length == 5)
		print_double(va_arg(argptr, long double));
	else if (g_flags.symbol == 'o' && g_flags.length == 3)
		print_octal(va_arg(argptr, unsigned long));
	else if (g_flags.symbol == 'o' && g_flags.length == 4)
		print_octal(va_arg(argptr, unsigned long long));
}

static void	prepare_to_print2(va_list argptr)
{
	if (g_flags.symbol == 'p')
		print_address_hex(va_arg(argptr, void *));
	else if ((g_flags.symbol == 'x' || g_flags.symbol == 'X')
			&& g_flags.length == 0)
		print_hex(va_arg(argptr, unsigned int), 0);
	else if ((g_flags.symbol == 'x' || g_flags.symbol == 'X')
			&& g_flags.length == 1)
		print_hex((unsigned short)va_arg(argptr, int), 0);
	else if ((g_flags.symbol == 'x' || g_flags.symbol == 'X')
			&& g_flags.length == 2)
		print_hex((unsigned char)va_arg(argptr, int), 0);
	else if ((g_flags.symbol == 'x' || g_flags.symbol == 'X')
			&& g_flags.length == 3)
		print_hex(va_arg(argptr, unsigned long), 0);
	else if ((g_flags.symbol == 'x' || g_flags.symbol == 'X')
			&& g_flags.length == 4)
		print_hex(va_arg(argptr, unsigned long long), 0);
	else if (g_flags.symbol == 'o' && g_flags.length == 0)
		print_octal(va_arg(argptr, unsigned int));
	else if (g_flags.symbol == 'o' && g_flags.length == 1)
		print_octal((unsigned short)va_arg(argptr, int));
	else if (g_flags.symbol == 'o' && g_flags.length == 2)
		print_octal((unsigned char)va_arg(argptr, int));
	else
		prepare_to_print3(argptr);
}

void		prepare_to_print(va_list argptr)
{
	if ((g_flags.symbol == 'i' || g_flags.symbol == 'd')
			&& g_flags.length == 0)
		print_int(va_arg(argptr, int));
	else if ((g_flags.symbol == 'i' || g_flags.symbol == 'd')
			&& g_flags.length == 1)
		print_int((short)va_arg(argptr, int));
	else if ((g_flags.symbol == 'i' || g_flags.symbol == 'd')
			&& g_flags.length == 2)
		print_int((signed char)va_arg(argptr, int));
	else if ((g_flags.symbol == 'i' || g_flags.symbol == 'd')
			&& g_flags.length == 3)
		print_int(va_arg(argptr, long));
	else if ((g_flags.symbol == 'i' || g_flags.symbol == 'd')
			&& g_flags.length == 4)
		print_int(va_arg(argptr, long long int));
	else if (g_flags.symbol == 'c')
		print_char((char)va_arg(argptr, int));
	else if (g_flags.symbol == '%')
		print_char('%');
	else if (g_flags.symbol == 's')
		print_str(va_arg(argptr, char *));
	else
		prepare_to_print2(argptr);
}
