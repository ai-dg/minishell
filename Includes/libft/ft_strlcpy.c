/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: calbor-p <calbor-p@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/07 10:16:09 by calbor-p          #+#    #+#             */
/*   Updated: 2023/11/15 18:10:46 by calbor-p         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcpy(char *dst, const char *src, size_t size)
{
	size_t	count;
	size_t	srclen;

	count = 0;
	srclen = ft_strlen(src);
	if (size == 0)
		return (srclen);
	if (size >= 1)
	{
		while (src[count] && count < size - 1)
		{
			dst[count] = src[count];
			count++;
		}
	}
	dst[count] = '\0';
	return (srclen);
}
/*
#include <stdio.h>

int	main(void)
{
	char src[] = "coucou";
	char dest[10]; memset(dest, 'A', 10);
	int len = ft_strlcpy(dest, src, 0);

	printf("%d, %s", len, dest);
	return (0);
	
}*/