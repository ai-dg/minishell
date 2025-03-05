/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: calbor-p <calbor-p@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/06 13:44:40 by calbor-p          #+#    #+#             */
/*   Updated: 2023/11/26 07:13:53 by calbor-p         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_putnbr_long(long nb)
{
	long long	nbr;

	nbr = nb;
	if (nbr < 0)
	{
		nbr = -nbr;
		ft_putchar(45);
	}
	if (nbr < 10 && nbr >= 0)
	{
		ft_putchar(nbr + 48);
	}
	if (nbr >= 10)
	{
		ft_putnbr(nbr / 10);
		ft_putchar(nbr % 10 + 48);
	}
}

void	ft_putnbr(int nb)
{
	long	nbr;

	nbr = nb;
	if (nbr < 0)
	{
		nbr = -nbr;
		ft_putchar(45);
	}
	if (nbr < 10 && nbr >= 0)
	{
		ft_putchar(nbr + 48);
	}
	if (nbr >= 10)
	{
		ft_putnbr(nbr / 10);
		ft_putchar(nbr % 10 + 48);
	}
}
/*
int	main(void){
	ft_putnbr(-2147483648);
}
*/