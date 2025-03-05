/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handler_params.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ls <ls@student.42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/02 12:45:22 by calbor-p          #+#    #+#             */
/*   Updated: 2024/04/29 20:17:33 by ls               ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	handle_params_int(char *params, int i, int reads, t_offsets off)
{
	if (i < 0)
		reads += write_char('-');
	if ((params[0] == '0') && !is_in_array('-', params)
		&& off.b_space > off.s_length && !is_in_array('.', params))
		reads += print_char(off.b_space - off.s_length, '0');
	if (is_in_array('.', params) && off.precision >= off.length)
	{
		if (i == 0)
			off.length = 0;
		if (i <= 0)
			reads += print_char(off.precision - off.length, '0');
		else
			reads += print_char(off.precision - off.s_length, '0');
	}
	if (!is_in_array('.', params) || (is_in_array('.', params)
			&& (off.precision >= 0 && i != 0)))
		reads += write_number(i, false);
	if (params[0] == '-' && off.a_space != 0 && off.a_space > reads)
		reads += print_char(off.a_space - reads, ' ');
	return (reads);
}

int	handle_params_uint(char *params, unsigned int i, int reads, t_offsets off)
{
	if ((params[0] == '0') && !is_in_array('-', params)
		&& off.b_space > off.length && !is_in_array('.', params))
		reads += print_char(off.b_space - off.length, '0');
	if (is_in_array('.', params) && off.precision >= off.length)
	{
		if (i == 0)
			off.length = 0;
		reads += print_char(off.precision - off.length, '0');
	}
	if (!is_in_array('.', params) || (is_in_array('.', params)
			&& (off.precision >= 0 && i != 0)))
		reads += write_number(i, false);
	if (params[0] == '-' && off.a_space != 0 && off.a_space > reads)
		reads += print_char(off.a_space - reads, ' ');
	return (reads);
}
