/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handler_hex.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ls <ls@student.42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/02 17:30:39 by calbor-p          #+#    #+#             */
/*   Updated: 2023/12/22 18:01:47 by ls               ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	manage_limits(long long int lnbr, char *params)
{
	int	reads;

	reads = 0;
	if ((unsigned long int)lnbr == ULONG_MAX)
		reads = write_str("0xffffffffffffffff");
	if (lnbr == LONG_MIN)
		reads = write_str("0x8000000000000000");
	if (params[0] == '-' && extract_number(params) != 0
		&& extract_number(params) > reads)
		reads += print_char(extract_number(params) - reads, ' ');
	return (reads);
}

int	manage_nullptr(char *params)
{
	int	reads;

	reads = 0;
	if (ft_isdigit(params[0]) && extract_number(params) > 5)
		reads += print_char(extract_number(params) - 5, ' ');
	reads += write_str("(nil)");
	return (reads);
}

int	ft_printhex(long long int lnbr, int start, char *base)
{
	static int	nb = 0;

	if (lnbr < 0)
		lnbr = 4294967296 - (lnbr * -1);
	if (start == -1)
		nb = 0;
	if (lnbr < 16 && lnbr >= 0)
	{
		ft_putchar(base[lnbr]);
		return (++nb);
	}
	if (lnbr >= 16)
	{
		nb++;
		ft_printhex(lnbr / 16, 1, base);
		ft_putchar(base[lnbr % 16]);
	}
	return (nb);
}

int	ft_printnbr_hex(long long int lnbr, char *base)
{
	int	reads;

	reads = 0;
	reads += write_str("0x");
	reads += ft_printhex(lnbr, -1, base);
	return (reads);
}

int	handle_pointer(va_list args, char *params)
{
	long long int	p;
	char			*base;
	int				reads;

	reads = 0;
	base = "0123456789abcdef";
	p = (long long int)va_arg(args, int *);
	if (p == 0)
		return (manage_nullptr(params));
	if (ft_isdigit(params[0])
		&& extract_number(params) > count_digits_from_hex(p, -1) + 2)
		reads += print_char(extract_number(params) - count_digits_from_hex(p,
					-1) - 2, ' ');
	if ((unsigned long int)p == ULONG_MAX || p == LONG_MIN)
		reads += manage_limits(p, params);
	else
	{
		reads += ft_printnbr_hex(p, base);
		if (params[0] == '-' && (extract_number(params) != 0
				&& extract_number(params) > reads))
			reads += print_char(extract_number(params) - reads, ' ');
	}
	return (reads);
}
