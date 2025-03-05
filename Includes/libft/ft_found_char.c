/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_found_char.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dagudelo <dagudelo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/03 07:35:42 by ls                #+#    #+#             */
/*   Updated: 2024/06/08 15:32:18 by dagudelo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

// bool	ft_found_char(char *str, int c)
// {
// 	int	i;

// 	i = 0;
// 	if (!str)
// 		return (false);
// 	while (str[i])
// 	{
// 		if (str[i] == c)
// 			return (true);
// 		i++;
// 	}
// 	return (false);
// }

bool	ft_found_char(char *str, int c)
{
	int	i;

	i = 0;
	if (str == NULL)
	{
		return (false);
	}
	while (str[i] != '\0')
	{
		if (str[i] == c)
		{
			return (true);
		}
		i++;
	}
	return (false);
}
