/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: calbor-p <calbor-p@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/17 16:14:05 by calbor-p          #+#    #+#             */
/*   Updated: 2023/11/17 16:14:09 by calbor-p         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

static char	*trim_whitespace(char *str)
{
	while (*str == ' ' || (*str >= 9 && *str <= 13))
	{
		str++;
	}
	return (str);
}

static int	get_number(char *str)
{
	int	count;
	int	n;

	n = 0;
	count = 0;
	while (str[count] >= '0' && str[count] <= '9')
	{
		n = n * 10 + str[count] - '0';
		count++;
	}
	return (n);
}

int	ft_atoi(const char *nptr)
{
	int		sign;
	int		number;
	char	*str;

	str = (char *)nptr;
	sign = 1;
	str = trim_whitespace(str);
	if (str[0] == '+' || str[0] == '-')
	{
		if (str[0] == '-')
			sign *= -1;
		str++;
	}
	number = get_number(str) * sign;
	return (number);
}
