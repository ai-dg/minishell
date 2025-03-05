/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: calbor-p <calbor-p@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/17 16:17:12 by calbor-p          #+#    #+#             */
/*   Updated: 2023/11/18 15:48:28 by calbor-p         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *haystack, const char *needle, size_t n)
{
	size_t	i;
	size_t	j;
	int		length;
	char	*str;

	if ((!haystack || !needle) && n == 0)
		return (0);
	str = (char *)haystack;
	i = 0;
	j = 0;
	length = 0;
	while (needle[length])
		length++;
	if (length == 0)
		return (str);
	while (haystack[i] && i < n)
	{
		j = 0;
		while (str[i + j] == needle[j] && i + j < n)
			if (needle[j++ + 1] == '\0')
				return (str + i);
		i++;
	}
	return (0);
}
