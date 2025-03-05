/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: calbor-p <calbor-p@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/17 16:17:17 by calbor-p          #+#    #+#             */
/*   Updated: 2023/11/18 13:54:14 by calbor-p         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	int				i;
	char			*tmp;
	unsigned char	cc;

	i = (int)ft_strlen((char *)s);
	tmp = (char *)s + i;
	cc = (unsigned char)c;
	while (*tmp != cc)
	{
		if (i == 0)
			return (NULL);
		tmp--;
		i--;
	}
	return (tmp);
}
