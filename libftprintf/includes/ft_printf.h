/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libftprintf.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybuhai <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/11 11:37:00 by ybuhai            #+#    #+#             */
/*   Updated: 2019/01/16 13:57:23 by ybuhai           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H
# include <stdarg.h>
# include "../libft/libft.h"

unsigned long long	g_count;
struct
{
	char			flag[5];
	int				width;
	int				length;
	int				precision;
	int				symbol;
}					g_flags;

int					ft_printf(const char *format, ...);
void				ft_put_char(int c);
int					intlen(__int128 n);
int					check_width(const char *str);
int					check_length(const char *str, int *i);
int					check_symbol(char c);
int					ft_a_toi(const char *str);
int					check_precision(const char *str);
void				prepare_to_print(va_list argptr);
void				print_char(int c);
void				print_str(char *str);
void				print_int(__int128 nbr);
void				struct_to_nul(void);
void				print_address_hex(void *p0);
void				fill_str(char *str, int *i);
void				print_ptr(char *str);
void				print_hex(__int128 nbr, int f);
void				print_double(long double nbr);
void				print_octal(unsigned long long nbr);
void				print_first_ptr(char *str, int nulls_before, int free_p);
void				print_last_ptr(char *str, int nulls_before, int free_place);
int					ft_getdouble_len(long double value, long double *limit);
int					get_float_bit(long double num, long double limit);
long double			round_off(long double nbr);

#endif
