/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strstr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dagudelo <dagudelo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/23 10:49:24 by dagudelo          #+#    #+#             */
/*   Updated: 2024/06/19 10:10:32 by dagudelo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strstr(char *str, char *to_find)
{
	int	str_pos;
	int	to_find_pos;

	str_pos = 0;
	to_find_pos = 0;
	if (to_find && to_find[0] == '\0')
		return ((char *)str);
	while (str != NULL && str[str_pos])
	{
		to_find_pos = 0;
		if (str && to_find && str[str_pos] && to_find[to_find_pos])
		{
			while (str[str_pos + to_find_pos] == to_find[to_find_pos])
			{
				to_find_pos++;
				if (!to_find[to_find_pos])
					return (&str[str_pos]);
			}
		}
		str_pos++;
	}
	return (0);
}

char	*ft_strrstr(char *str, char *to_find)
{
	int	str_pos;
	int	to_find_pos;

	str_pos = 0;
	to_find_pos = 0;
	if (to_find[0] == '\0')
		return ((char *)str);
	while (str != NULL && str[str_pos])
	{
		to_find_pos = 0;
		if (str[str_pos] && to_find[to_find_pos])
		{
			while (str[str_pos + to_find_pos] == to_find[to_find_pos])
			{
				to_find_pos++;
				if (!to_find[to_find_pos])
					return (&str[str_pos]);
			}
		}
		str_pos++;
	}
	return (0);
}
