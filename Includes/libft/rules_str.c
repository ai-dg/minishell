/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rules_str.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ls <ls@student.42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/09 05:27:03 by ls                #+#    #+#             */
/*   Updated: 2023/12/22 18:02:24 by ls               ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	check_space_rule_str(t_offsets off, int reads, char *params)

{
	if (params[0] == ' ' && off.length > off.b_space && off.b_space > 0)
		reads += print_char(off.b_space - off.length, ' ');
	if (params[0] == ' ' && off.length == 0)
		reads += print_char(off.b_space, ' ');
	return (reads);
}

int	check_dot_rule_str(t_offsets off, int reads, char *s, char *params)
{
	if (is_in_array('.', params))
	{
		if (off.precision < off.length && off.b_space > 0)
			reads += print_char(off.b_space - off.precision, ' ');
		else
			reads += print_char(off.b_space, ' ');
		reads = write_nstr(s, off.precision) + reads;
	}
	else
		reads = write_str(s) + reads;
	return (reads);
}

int	check_minus_rule_str(t_offsets off, int reads, char *params)
{
	if (params[0] == '-' && !is_in_array('.', params)
		&& off.length < off.a_space && off.a_space > 0)
		reads += print_char(off.a_space - off.length, ' ');
	if (params[0] == '-' && is_in_array('.', params) && off.length < off.a_space
		&& off.a_space > 0)
	{
		if (off.length > off.precision)
			reads += print_char(off.a_space - off.precision, ' ');
		else
			reads += print_char(off.a_space - off.length, ' ');
	}
	return (reads);
}

int	check_zero_rule_str(t_offsets off, int reads, char *params)
{
	if (ft_isdigit(params[0]) && params[0] != '0' && (off.b_space > off.length))
		reads += print_char(off.b_space - off.length, ' ');
	return (reads);
}
