/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_convert_base2.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: calbor-p <calbor-p@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/15 16:38:59 by calbor-p          #+#    #+#             */
/*   Updated: 2024/02/14 13:50:30 by calbor-p         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*check_base(char *base, char *check)
{
	int		count;
	char	temp;

	count = 0;
	while (base[count])
	{
		check[count] = base[count];
		count++;
	}
	check[count] = '\0';
	count = 1;
	while (check[count])
	{
		if (check[count - 1] > check[count])
		{
			temp = check[count - 1];
			check[count -1] = check[count];
			check[count] = temp;
			count = 1;
		}
		count++;
	}
	return (check);
}

int	check_error(char *base)
{
	int		i;
	char	check[1000];

	i = 0;
	while (base[i])
	{
		if ((base[i] == '+' || base[i] == '-')
			|| check_base(base, check)[i] == check_base(base, check)[i - 1]
				|| base[i] == ' ' || (base[i] >= 9 && base[i] <= 13))
		{
			return (1);
		}
		i++;
	}
	if (i < 2)
		return (1);
	return (0);
}

int	in_base(char *base, char c, int *getindex)
{
	int	count;
	int	match;

	count = 0;
	match = 0;
	while (base[count])
	{
		if (base[count] == c)
		{
			match++;
			*getindex = count;
		}
		count ++;
	}
	return (match);
}

long	get_number(char *str, char *base)
{
	int		count;
	long	n;
	int		index;
	int		*getindex;
	int		base_length;

	base_length = 0;
	while (base[base_length])
		base_length++;
	n = 0;
	count = 0;
	getindex = &index;
	while (in_base(base, str[count], getindex))
	{
		n = n * base_length + *getindex;
		count++;
	}
	return (n);
}

long	ft_atoi_base(char *str, char *base)
{
	int		sign;
	long	number;

	if (!check_error(base))
	{
		sign = 1;
		while (*str == ' ' || (*str >= 9 && *str <= 13))
			str++;
		while (*str == '+' || *str == '-')
		{
			if (*str == '-')
				sign *= -1;
			str++;
		}
		number = get_number(str, base) * sign;
		return (number);
	}
	return (0);
}
