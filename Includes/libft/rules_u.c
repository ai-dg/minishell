/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rules_u.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ls <ls@student.42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/09 04:08:44 by ls                #+#    #+#             */
/*   Updated: 2023/12/22 18:02:31 by ls               ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	check_zero_rule_u(t_offsets off, int reads, int nbr, char *params)
{
	if (ft_isdigit(params[0]) && params[0] != '0' && off.b_space > off.length)
	{
		if (is_in_array('.', params) && off.precision < off.b_space)
			reads += print_char(off.b_space - off.precision, ' ');
		else
			reads += print_char(off.b_space - off.length, ' ');
	}
	if (params[0] == '0' && is_in_array('.', params) && off.b_space > off.length
		&& off.b_space > off.precision && nbr != 0)
	{
		if (off.precision < off.length)
			reads += print_char(off.b_space - off.length, ' ');
		else
			reads += print_char(off.b_space - off.precision, ' ');
	}
	if (params[0] == '0' && is_in_array('.', params) && off.precision == 0
		&& nbr == 0)
		reads += print_char(off.b_space, ' ');
	return (reads);
}

int	check_space_rule_u(t_offsets off, int reads, int nbr, char *params)
{
	if (params[0] == ' ' && off.length < off.b_space && off.b_space > 0)
		reads += print_char(off.b_space - off.length, ' ');
	if (nbr >= 0 && params[0] == ' ' && off.b_space == 0)
		reads += write_char(' ');
	return (reads);
}
