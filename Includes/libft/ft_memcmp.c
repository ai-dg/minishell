/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: calbor-p <calbor-p@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/17 16:14:56 by calbor-p          #+#    #+#             */
/*   Updated: 2023/11/17 16:14:58 by calbor-p         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_memcmp(const void *s1, const void *s2, size_t n)
{
	unsigned char	*sc1;
	unsigned char	*sc2;
	size_t			i;

	sc1 = (unsigned char *)s1;
	sc2 = (unsigned char *)s2;
	i = -1;
	while (++i < n)
		if (sc1[i] != sc2[i])
			return (sc1[i] - sc2[i]);
	return (0);
}
/*
#include <stdio.h>

int	main(void)
{
	char	*test0;
	char	*test1;
	char	*test2;

	test0 = "ae teste une chaine";
	test1 = "je teste une chaine";
	test2 = "je teste une autre chaine";
	int a, b, c, d;
	a = memcmp(test0, test1, 12);
	b = memcmp(test1, test2, 12);
	c = ft_memcmp(test0, test1, 15);
	d = ft_memcmp(test1, test2, 15);
	printf("avec memcmp : %d    %d\n", a, b);
	printf("avec ft_memcmp : %d    %d\n", c, d);
}*/