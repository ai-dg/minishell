/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: calbor-p <calbor-p@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/06 16:50:42 by calbor-p          #+#    #+#             */
/*   Updated: 2023/11/18 15:38:19 by calbor-p         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memcpy(void *dest, const void *src, size_t n)
{
	char	*temp;

	if ((dest == 0 && src == 0) && n != 0)
		return (0);
	temp = (char *)dest;
	while (n--)
		*temp++ = *(char *)src++;
	return (dest);
}
