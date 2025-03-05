/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handler_numb.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ls <ls@student.42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/26 07:34:57 by calbor-p          #+#    #+#             */
/*   Updated: 2024/04/29 20:17:49 by ls               ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	handle_int(va_list args, char *params)
{
	int			nbr;
	int			reads;
	t_offsets	off;

	nbr = va_arg(args, int);
	off = extract_params(params);
	off.length = count_digits_from_nb(nbr, false);
	off.s_length = count_digits_from_nb(nbr, true);
	reads = 0;
	reads += check_plus_rule_i(nbr, params);
	reads = check_zero_rule_i(off, reads, nbr, params);
	reads = check_space_rule_i(off, reads, nbr, params);
	reads = handle_params_int(params, nbr, reads, off);
	return (reads);
}

int	handle_unsigned(va_list args, char *params)
{
	int			nbr;
	int			reads;
	t_offsets	off;

	nbr = va_arg(args, unsigned int);
	off = extract_params(params);
	if (nbr < 0)
		nbr = 4294967296 - (nbr * -1);
	off.length = count_digits_from_uint(nbr);
	reads = 0;
	reads = check_zero_rule_u(off, reads, nbr, params);
	reads = check_space_rule_u(off, reads, nbr, params);
	reads = handle_params_uint(params, nbr, reads, off);
	return (reads);
}

int	handle_hex(char *params, char *base, t_offsets off, int reads)
{
	reads = sharp_rule(off, reads, params);
	reads = check_zero_rule_hex(off, reads, params);
	reads = check_dot_rule_hex(off, reads, params);
	reads = check_minus_rule_hex(off, reads, params, base);
	return (reads);
}

int	handle_hexlower(va_list args, char *params)
{
	char		*base;
	int			reads;
	t_offsets	off;

	off = extract_params(params);
	off.nbr = va_arg(args, int);
	off.length = count_digits_from_hex(off.nbr, -1);
	off.s_length = count_digits_from_hex(off.nbr, -1);
	off.c = 'x';
	reads = 0;
	base = "0123456789abcdef";
	reads = handle_hex(params, base, off, reads);
	return (reads);
}

int	handle_hexupper(va_list args, char *params)
{
	char		*base;
	int			reads;
	t_offsets	off;

	off = extract_params(params);
	off.nbr = va_arg(args, int);
	off.length = count_digits_from_hex(off.nbr, -1);
	off.s_length = count_digits_from_hex(off.nbr, -1);
	off.c = 'X';
	reads = 0;
	base = "0123456789ABCDEF";
	reads = handle_hex(params, base, off, reads);
	return (reads);
}
