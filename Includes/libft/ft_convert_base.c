/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_convert_base.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dagudelo <dagudelo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/15 16:38:52 by calbor-p          #+#    #+#             */
/*   Updated: 2024/06/25 12:26:28 by dagudelo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_charcat(char *dest, char src)
{
	int		dest_len;

	dest_len = 0;
	while (dest[dest_len] != '\0')
		dest_len++;
	dest[dest_len] = src;
	dest[dest_len + 1] = '\0';
	return (dest);
}

char	*ft_putstr_base(long nbr, char *base, char *str)
{
	long	lnbr;
	long	base_size;

	lnbr = (long)nbr;
	base_size = (long) ft_strlen(base);
	if (!check_error(base))
	{
		if (lnbr < 0 && lnbr >= -2147483648)
		{
			lnbr = -lnbr;
			str[0] = '-';
		}
		if (lnbr < base_size && lnbr >= 0)
		{
			ft_charcat(str, base[lnbr]);
		}
		if (lnbr >= base_size)
		{
			ft_putstr_base(lnbr / base_size, base, str);
			ft_charcat(str, base[lnbr % base_size]);
		}
		return (str);
	}
	return (0);
}

char	*ft_convert_base(char *nbr, char *base_from, char *base_to)
{
	long	to_convert;
	char	*converted;

	if (!nbr || !base_from || !base_to)
		return (0);
	converted = malloc(33 * sizeof(char));
	if (!converted)
		return (0);
	if (check_error(base_from) && check_error(base_to))
	{
		free(converted);
		return (0);
	}
	converted[0] = 0;
	to_convert = ft_atoi_base(nbr, base_from);
	converted = ft_putstr_base(to_convert, base_to, converted);
	return (converted);
}
