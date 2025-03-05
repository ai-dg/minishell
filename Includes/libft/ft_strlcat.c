/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ls <ls@student.42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/09 18:28:13 by calbor-p          #+#    #+#             */
/*   Updated: 2024/05/11 14:11:47 by ls               ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <bsd/string.h>

size_t	ft_strlcat(char *dst, const char *src, size_t size)
{
	size_t	len_dst;
	size_t	len_src;
	size_t	total_len;
	size_t	i;
	size_t	j;

	len_dst = ft_strlen(dst);
	len_src = ft_strlen(src);
	total_len = len_dst + len_src + 1;
	i = len_dst;
	j = 0;
	size = size + len_dst;
	while (i < size)
	{
		dst[i] = src[j];
		i++;
		j++;
	}
	dst[i] = '\0';
	return (total_len);
}

/*
#include <bsd/string.h>
#include <stdio.h>

int	main(void)
{

	int	test;
	int	test2;
	char *dest;
	char *dest1;

	dest = malloc(sizeof(*dest)*15);
	if (!dest)
		return (0);
	dest1 = malloc(sizeof(*dest1)*15);
	if (!dest1)
		return (0);
	memset(dest, 'r', 14);
	memset(dest1, 'r', 14);


		test = ft_strlcat(dest, "lorem ipsum dolor sit amet", 5);


		test2 = strlcat(dest1, "lorem ipsum dolor sit amet", 5);
		printf("ft_strlcat : %s\n",dest);
		printf("valeur de retour : %d\n", test);
		printf("----------------------------\n");
		printf("   strlcat : %s\n",dest1);
		printf("valeur de retour : %d\n", test2);
		printf("comparaison : %d\n", test == test2);
		free(dest);
		free(dest1);
}*/
/*
31
rrrrrrrrrrrrrrr

	memset(dest, 'r', 15);
		ft_print_result(ft_strlcat(dest, "lorem ipsum dolor sit amet", 5));
		write(1, "\n", 1);
		write(1, dest, 15);

*/