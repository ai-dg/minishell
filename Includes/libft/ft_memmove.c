/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: calbor-p <calbor-p@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/17 16:15:28 by calbor-p          #+#    #+#             */
/*   Updated: 2023/11/18 15:38:25 by calbor-p         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dest, const void *src, size_t n)
{
	char	*source;
	char	*destination;

	if ((dest == 0 && src == 0) && n != 0)
		return (0);
	source = (char *)src;
	destination = (char *)dest;
	if (destination < source)
	{
		while (n--)
			*destination++ = *source++;
	}
	else
	{
		source = source + (n - 1);
		destination = destination + (n - 1);
		while (n--)
			*destination-- = *source--;
	}
	return (dest);
}
