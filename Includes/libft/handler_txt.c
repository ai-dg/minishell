/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handler_txt.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ls <ls@student.42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/26 07:30:24 by calbor-p          #+#    #+#             */
/*   Updated: 2023/12/22 18:01:59 by ls               ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	handle_char(va_list args, char *params)
{
	char		c;
	int			reads;
	t_offsets	off;

	off = extract_params(params);
	off.length = 1;
	reads = 0;
	c = va_arg(args, int);
	if (ft_isdigit(params[0]) && extract_number(params) > 1)
		reads += print_char(extract_number(params) - 1, ' ');
	ft_putchar(c);
	if (params[0] == '-')
		if (off.a_space > 0)
			reads = print_char(off.a_space - 1, ' ');
	return (1 + reads);
}

int	handle_nullstr(char *params)
{
	int	reads;
	int	nb;

	nb = extract_number(params);
	reads = 0;
	if (ft_isdigit(params[0]) && params[0] != '0' && nb > 6)
		reads += print_char(nb - 6, ' ');
	if (params[0] == '.' && nb >= 6)
		return (reads += write_str("(null)"));
	if (params[0] == '.' && nb < 6)
		return (0);
	reads += write_str("(null)");
	return (reads);
	return (0);
}

int	handle_string(va_list args, char *params)
{
	char		*s;
	int			reads;
	t_offsets	off;

	s = va_arg(args, char *);
	off = extract_params(params);
	reads = 0;
	if (!s)
		return (handle_nullstr(params));
	off.length = (int)ft_strlen(s);
	reads = check_space_rule_str(off, reads, params);
	reads = check_zero_rule_str(off, reads, params);
	reads = check_dot_rule_str(off, reads, s, params);
	reads = check_minus_rule_str(off, reads, params);
	return (reads);
}

int	handle_percent(va_list args, char *params)
{
	(void)args;
	(void)params;
	ft_putchar('%');
	return (1);
}

int	print_char(int nb, char c)
{
	int	i;

	i = 0;
	while (i++ < nb)
		ft_putchar(c);
	return (nb);
}
