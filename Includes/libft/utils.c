/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ls <ls@student.42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/28 16:17:57 by calbor-p          #+#    #+#             */
/*   Updated: 2024/04/29 20:17:15 by ls               ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	count_digits_from_nb(long long int nb, bool count_sign)
{
	int	count;

	(void)count_sign;
	count = 0;
	if (nb == 0)
		return (1);
	if (nb < 0)
	{
		nb = -nb;
		if (count_sign > 0)
		{
			count++;
		}
	}
	while (nb > 0)
	{
		nb = nb / 10;
		count++;
	}
	return (count);
}

int	count_digits_from_uint(unsigned int nb)
{
	int	count;

	count = 0;
	if (nb == 0)
		return (1);
	while (nb > 0)
	{
		nb = nb / 10;
		count++;
	}
	return (count);
}

int	count_digits_from_hex(long long int lnbr, int start)
{
	static int	nb = 0;

	if (lnbr < 0)
		lnbr = 4294967296 - (lnbr * -1);
	if (start == -1)
		nb = 0;
	if (lnbr < 16 && lnbr >= 0)
		return (++nb);
	if (lnbr >= 16)
	{
		nb++;
		count_digits_from_hex(lnbr / 16, 1);
	}
	return (nb);
}

int	count_digits(char *params)
{
	int	i;
	int	j;
	int	count;

	i = 0;
	j = 0;
	count = 0;
	while (params[i])
	{
		if (ft_isdigit(params[i]))
		{
			j = i;
			while (ft_isdigit(params[j]))
			{
				count++;
				j++;
			}
			break ;
		}
		i++;
	}
	return (count);
}

int	extract_number(char *params)
{
	int	nb;
	int	i;

	i = 0;
	nb = 0;
	while (params[i])
	{
		if (ft_isdigit(params[i]))
		{
			nb = ft_atoi(&params[i]);
			break ;
		}
		i++;
	}
	return (nb);
}
