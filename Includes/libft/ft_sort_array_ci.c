/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_sort_array_ci.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ls <ls@student.42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/15 05:49:14 by calbor-p          #+#    #+#             */
/*   Updated: 2024/06/21 07:16:31 by ls               ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	compare_char_length(char *str1, char *str2)
{
	if (ft_strlen(str1) > ft_strlen(str2))
		return (2);
	else if (ft_strlen(str1) < ft_strlen(str2))
		return (1);
	return (0);
}

void	increment(int *i, int *j)
{
	*i = *i + 1;
	*j = *j + 1;
}

int	compare_ci(char *str1, char *str2)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	if (!str1 || !str2)
		return (-1);
	while (str1[i] && str2[j])
	{
		if (!ft_isalnum(str1[i]) && !ft_isalnum(str2[j]))
		{
			increment(&i, &j);
			continue ;
		}
		if (!ft_isalnum(str1[i]))
			i++;
		if (!ft_isalnum(str2[j]))
			j++;
		if (ft_tolower(str1[i]) > ft_tolower(str2[j]))
			return (2);
		else if (ft_tolower(str1[i]) < ft_tolower(str2[j]))
			return (1);
		increment(&i, &j);
	}
	return (compare_char_length(str1, str2));
}

void	ft_sort_array_ci(char **array)
{
	int	i;

	i = -1;
	while (array[++i])
	{
		if (array[i + 1])
		{
			if (compare_ci(array[i], array[i + 1]) == 1)
				ft_drop();
			else if (compare_ci(array[i], array[i + 1]) == 2)
			{
				ft_swap_chars(&array[i], &array[i + 1]);
				i = -1;
			}
		}
	}
}
