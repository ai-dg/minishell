/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   params.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ls <ls@student.42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/09 05:01:25 by ls                #+#    #+#             */
/*   Updated: 2023/12/22 18:02:10 by ls               ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_offsets	extract_params(char *params)
{
	t_offsets	off;

	off.a_space = 0;
	off.b_space = 0;
	off.precision = 0;
	off.length = 0;
	off.s_length = 0;
	off.blank = 0;
	off.nbr = 0;
	off.c = 'n';
	off.nbr = 0;
	if (ft_isdigit(params[0]) && extract_number(params) > 0)
		off.b_space = extract_number(params);
	if (params[0] == ' ' && ft_isdigit(params[1]))
		off.b_space = extract_number(params);
	if (is_in_array('.', params))
	{
		if (!ft_isdigit(params[find_index('.', params) + 1]))
			off.blank = 1;
		off.precision = extract_number(&params[find_index('.', params)]);
	}
	if (is_in_array('-', params))
		off.a_space = extract_number(params);
	return (off);
}
