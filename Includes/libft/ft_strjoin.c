/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: calbor-p <calbor-p@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/08 22:41:21 by calbor-p          #+#    #+#             */
/*   Updated: 2023/11/18 13:24:08 by calbor-p         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*Alloue (avec malloc(3)) et retourne un tableau
de chaînes de caractères obtenu en séparant ’s’ à
l’aide du caractère ’c’, utilisé comme délimiteur.
Le tableau doit être terminé par NULL.*/

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*res;
	int		t_len;

	if (!s1 || !s2)
		return (NULL);
	t_len = (int)ft_strlen(s1) + (int)ft_strlen(s2);
	if (t_len < 1)
	{
		res = malloc(sizeof(char) * 1);
		if (!res)
			return (NULL);
		res[0] = '\0';
		return (res);
	}
	else
		res = malloc(sizeof(char) * (t_len + 1));
	if (!res)
		return (NULL);
	while (*s1)
		*res++ = *s1++;
	while (*s2)
		*res++ = *s2++;
	*res = 0;
	return (res - t_len);
}
