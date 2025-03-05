/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rules_int.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ls <ls@student.42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/09 03:31:12 by ls                #+#    #+#             */
/*   Updated: 2023/12/22 18:02:19 by ls               ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	check_plus_rule_i(int nbr, char *params)
{
	int	reads;

	reads = 0;
	if (is_in_array('+', params))
		if (nbr >= 0)
			reads += write_char('+');
	return (reads);
}

int	check_zero_rule_i(t_offsets off, int reads, int nbr, char *params)
{
	if (ft_isdigit(params[0]) && params[0] != '0' && off.b_space > off.length)
	{
		if (is_in_array('.', params) && off.precision < off.b_space)
			reads += print_char(off.b_space - off.precision, ' ');
		else
			reads += print_char(off.b_space - off.s_length, ' ');
	}
	if (params[0] == '0' && is_in_array('.', params)
		&& off.b_space > off.s_length && off.b_space > off.precision
		&& nbr != 0)
	{
		if (off.precision < off.s_length)
			reads += print_char(off.b_space - off.s_length, ' ');
		else
		{
			if (nbr < 0)
				reads += print_char(off.b_space - off.precision - 1, ' ');
			else
				reads += print_char(off.b_space - off.precision, ' ');
		}
	}
	if (params[0] == '0' && is_in_array('.', params) && off.precision == 0
		&& nbr == 0)
		reads += print_char(off.b_space, ' ');
	return (reads);
}

int	check_space_rule_i(t_offsets off, int reads, int nbr, char *params)
{
	if (params[0] == ' ' && off.s_length < off.b_space && off.b_space > 0)
		reads += print_char(off.b_space - off.s_length, ' ');
	if (nbr >= 0 && params[0] == ' ' && off.b_space == 0)
		reads += write_char(' ');
	return (reads);
}
