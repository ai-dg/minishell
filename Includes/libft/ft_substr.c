/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ls <ls@student.42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/17 16:17:30 by calbor-p          #+#    #+#             */
/*   Updated: 2023/12/31 06:47:52 by ls               ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*
	Alloue (avec malloc(3)) et retourne une chaîne de
	caractères issue de la chaîne ’s’.
	Cette nouvelle chaîne commence à l’index ’start’ et
	a pour taille maximale ’len’.
*/

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	size_t	i;
	char	*cpy;

	i = 0;
	if (!s)
		return (NULL);
	if (len + start > ft_strlen(s))
	{
		if (ft_strlen(s) > start)
			len = ft_strlen(s) - start;
		else
		{
			cpy = malloc(1);
			if (!cpy)
				cpy = NULL;
			return (cpy);
		}
	}
	cpy = malloc((len + 2));
	if (!cpy)
		return (NULL);
	while (i < len && s[start])
		cpy[i++] = s[start++];
	cpy[i] = '\0';
	return (cpy);
}
