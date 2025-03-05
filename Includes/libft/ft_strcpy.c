/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: calbor-p <calbor-p@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/28 08:10:14 by ls                #+#    #+#             */
/*   Updated: 2024/06/12 16:50:21 by calbor-p         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

// char	*ft_strcpy(char *dest, char *src)
// {
// 	int	i;

// 	i = -1;
// 	if (!dest || !src)
// 		return (NULL);
// 	while (src[++i])
// 		dest[i] = src[i];
// 	i++;
// 	dest[i] = '\0';
//     return (dest);
// }

char	*ft_strcpy(char *dest, char *src)
{
	int	i;

	if (!dest || !src)
		return (NULL);
	i = 0;
	while (src[i])
	{
		dest[i] = src[i];
		i++;
	}
	dest[i] = '\0';
	return (dest);
}
