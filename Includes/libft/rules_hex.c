/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rules_hex.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ls <ls@student.42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/09 04:14:40 by ls                #+#    #+#             */
/*   Updated: 2023/12/22 18:02:15 by ls               ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	sharp_rule(t_offsets off, int reads, char *params)
{
	if (is_in_array('#', params))
	{
		if (off.nbr != 0)
		{
			reads += write_char('0');
			reads += write_char(off.c);
		}
	}
	return (reads);
}

int	check_zero_rule_hex(t_offsets off, int reads, char *params)
{
	int	hlen;

	hlen = count_digits_from_hex(off.nbr, -1);
	if (params[0] == '0' && is_in_array('.', params) && off.nbr != 0)
	{
		if (off.length >= off.precision && off.b_space - off.length > 0)
			reads += print_char(off.b_space - off.length, ' ');
		else if (off.b_space > off.length && off.b_space - off.precision > 0)
			reads += print_char(off.b_space - off.precision, ' ');
		if (off.length < off.precision && off.precision - off.length > 0)
			reads += print_char(off.precision - off.length, '0');
	}
	if (params[0] == '0' && !is_in_array('-', params) && !is_in_array('.',
			params) && off.b_space > hlen && off.nbr != 0)
		reads += print_char(off.b_space - hlen, '0');
	if (ft_isdigit(params[0]) && params[0] != '0' && off.b_space > hlen
		&& off.nbr != 0)
		reads += print_char(off.b_space - hlen, ' ');
	if (params[0] == '0' && off.nbr == 0 && !is_in_array('.', params))
		reads += print_char(off.b_space - 1, '0');
	return (reads);
}

int	check_dot_rule_hex(t_offsets off, int reads, char *params)
{
	int	hlen;

	hlen = count_digits_from_hex(off.nbr, -1);
	if (params[0] == '.' && off.b_space > hlen && off.nbr != 0)
		reads += print_char(off.b_space - off.precision - hlen, '0');
	if (params[0] == '.' && off.b_space == 0 && off.precision > hlen
		&& off.nbr != 0)
		reads += print_char(off.precision - hlen, '0');
	if (is_in_array('.', params) && off.b_space > 0 && off.precision == 0)
	{
		if (off.nbr == 0)
			off.length = 0;
		reads = print_char(off.b_space - off.length, ' ');
	}
	if ((is_in_array('.', params) && (off.precision > 0 && off.nbr == 0)))
		reads += print_char(off.precision, '0');
	return (reads);
}

int	check_minus_rule_hex(t_offsets off, int reads, char *params, char *base)
{
	int	hlen;

	hlen = count_digits_from_hex(off.nbr, -1);
	if (is_in_array('-', params) && is_in_array('.', params) && off.precision
		- hlen > 0 && off.nbr != 0)
		reads += print_char(off.precision - hlen, '0');
	if (!is_in_array('.', params) || (is_in_array('.', params)
			&& (off.precision >= 0 && off.nbr != 0)))
		reads += ft_printhex(off.nbr, -1, base);
	if (is_in_array('-', params) && !is_in_array('.', params)
		&& off.a_space != 0 && off.a_space > reads)
		reads += print_char(off.a_space - reads, ' ');
	if (is_in_array('-', params) && is_in_array('.', params) && off.a_space != 0
		&& off.a_space > reads)
		reads += print_char(off.a_space - reads, ' ');
	return (reads);
}
