/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_sort_array_cs.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dagudelo <dagudelo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/14 17:58:02 by calbor-p          #+#    #+#             */
/*   Updated: 2024/06/15 13:07:47 by dagudelo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	compare_cs(char *str1, char *str2)
{
	int	i;

	i = 0;
	if (!str1 || !str2)
		return (-1);
	while (str1[i] && str2[i])
	{
		if (str1[i] > str2[i])
			return (2);
		else if (str1[i] < str2[i])
			return (1);
		i++;
	}
	if (ft_strlen(str1) > ft_strlen(str2))
		return (2);
	if (ft_strlen(str1) < ft_strlen(str2))
		return (1);
	return (0);
}

void	ft_sort_array_cs(char **array)
{
	int	i;

	i = -1;
	while (array[++i])
	{
		if (array[i + 1])
		{
			if (compare_cs(array[i], array[i + 1]) == 1)
			{
			}
			else if (compare_cs(array[i], array[i + 1]) == 2)
			{
				ft_swap_chars(&array[i], &array[i + 1]);
				i = -1;
			}
		}
	}
}
