/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   string_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: calbor-p <calbor-p@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/04 22:52:10 by ls                #+#    #+#             */
/*   Updated: 2024/06/12 16:46:42 by calbor-p         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	swap_char(char *c1, char *c2)
{
	char	tmp;

	tmp = *c1;
	*c1 = *c2;
	*c2 = tmp;
}

bool	is_strictly_alternating(char *str, char c1, char c2)
{
	int	i;

	if (!str)
		return (false);
	i = -1;
	if (str[0] != c1)
		swap_char(&c1, &c2);
	while (str[++i])
	{
		if (i % 2 == 0)
		{
			if (str[i] != c1)
				return (false);
		}
		else if (i % 2 != 0)
		{
			if (str[i] != c2)
				return (false);
		}
	}
	return (true);
}

bool	is_strictly_alternating_within(char *str, char c1, char c2, int max)
{
	int	i;

	if (!str)
		return (false);
	i = -1;
	if (str[0] != c1)
		swap_char(&c1, &c2);
	while (str[++i] && i <= max)
	{
		if (i % 2 == 0)
		{
			if (str[i] != c1)
				return (false);
		}
		else if (i % 2 != 0)
		{
			if (str[i] != c2)
				return (false);
		}
	}
	return (true);
}
