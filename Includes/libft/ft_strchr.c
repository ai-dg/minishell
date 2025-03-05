/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: calbor-p <calbor-p@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/17 16:16:27 by calbor-p          #+#    #+#             */
/*   Updated: 2024/05/06 16:41:59 by calbor-p         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strchr(const char *s, int c)
{
	size_t			i;
	size_t			len;
	unsigned char	cc;

	cc = (unsigned char)c;
	i = 0;
	len = ft_strlen(s);
	while (*s != cc)
	{
		if (i == len || len == 0)
			return (NULL);
		s++;
		i++;
	}
	return ((char *)s);
}

/*
#include <stdio.h>

int	main(void)
{
	printf("avec ft_strchr\n");
	char *test = "ceci est ma chaine de test";
	char *test2 = (char *)ft_strchr(test, 'm');
	printf("adresse : %p\n", ft_strchr(test, 'm'));
	printf("%s\n",test2);
	printf("avec strchr\n");
	char *test3 = (char *)strchr(test, 'm');
	printf("adresse : %p\n", strchr(test, 'm'));
	printf("%s\n",test3);
}*/
