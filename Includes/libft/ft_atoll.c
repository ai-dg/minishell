/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoll.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ls <ls@student.42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/22 23:38:43 by ls                #+#    #+#             */
/*   Updated: 2024/05/22 23:45:42 by ls               ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static char	*trim_whitespace(char *str)
{
	while (*str == ' ' || (*str >= 9 && *str <= 13))
	{
		str++;
	}
	return (str);
}

static long long int	get_long_number(char *str)
{
	int				count;
	long long int	n;

	n = 0;
	count = 0;
	while (str[count] >= '0' && str[count] <= '9')
	{
		n = n * 10 + str[count] - '0';
		count++;
	}
	return (n);
}

long long int	ft_atoll(const char *nptr)
{
	int				sign;
	long long int	number;
	char			*str;

	str = (char *)nptr;
	sign = 1;
	str = trim_whitespace(str);
	if (str[0] == '+' || str[0] == '-')
	{
		if (str[0] == '-')
			sign *= -1;
		str++;
	}
	number = get_long_number(str) * sign;
	return (number);
}
