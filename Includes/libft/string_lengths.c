/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   string_lengths.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ls <ls@student.42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/04 22:43:49 by ls                #+#    #+#             */
/*   Updated: 2024/05/04 22:57:15 by ls               ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

bool	is_strlen_within_range(char *str, int min, int max)
{
	int	i;

	if (!str)
		return (false);
	i = 0;
	while (str[i])
		i++;
	if (i >= min && i <= max)
		return (true);
	return (false);
}

bool	is_strlen_greater_than(char *str, int max)
{
	int	i;

	i = 0;
	if (!str)
		return (false);
	while (str[i])
		i++;
	if (i > max)
		return (true);
	return (false);
}

bool	is_strlen_at_least(char *str, int min)
{
	int	i;

	i = 0;
	if (!str)
		return (false);
	while (str[i])
		i++;
	if (i >= min)
		return (true);
	return (false);
}

bool	is_strlen_within(char *str, int max)
{
	int	i;

	i = 0;
	if (!str)
		return (false);
	while (str[i])
		i++;
	if (i <= max)
		return (true);
	return (false);
}

bool	is_strlen_equal_to(char *str, int nb)
{
	int	i;

	i = 0;
	if (!str)
		return (false);
	while (str[i])
		i++;
	if (i == nb)
		return (true);
	return (false);
}
