/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handler_write.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ls <ls@student.42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/02 18:25:01 by calbor-p          #+#    #+#             */
/*   Updated: 2024/04/29 20:17:15 by ls               ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	write_char(char c)
{
	write(1, &c, 1);
	return (1);
}

int	write_str(char *str)
{
	int	i;

	i = 0;
	while (str[i])
		i += write_char(str[i]);
	return (i);
}

int	write_nstr(char *str, int len)
{
	int	i;

	i = 0;
	while (str[i] && len--)
		i += write_char(str[i]);
	return (i);
}

int	write_number(long nb, bool print_sign)
{
	long long	nbr;

	nbr = nb;
	if (nbr < 0)
	{
		nbr = -nbr;
		if (print_sign)
			ft_putchar(45);
	}
	if (nbr < 10 && nbr >= 0)
		ft_putchar(nbr + 48);
	if (nbr >= 10)
	{
		ft_putnbr(nbr / 10);
		ft_putchar(nbr % 10 + 48);
	}
	return (count_digits_from_nb(nb, print_sign));
}
