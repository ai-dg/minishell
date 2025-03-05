/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: calbor-p <calbor-p@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/17 16:16:58 by calbor-p          #+#    #+#             */
/*   Updated: 2023/11/18 13:22:48 by calbor-p         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*
Applique la fonction f à chaque caractère de la chaine de ca-
ractères passée en paramètre pour créer une nouvelle chaine
“fraiche” (avec malloc(3)) résultant des applications succes-
sives de f.
*/

char	*ft_strmapi(char const *s, char (*f)(unsigned int, char))
{
	int		size;
	int		i;
	char	*tmp;
	char	*new;

	if (!s || !f)
		return (NULL);
	tmp = (char *)s;
	i = 0;
	size = ft_strlen(tmp);
	new = malloc(size + 1 * sizeof(char));
	if (!new)
		return (NULL);
	while (i < size)
	{
		new[i] = f(i, tmp[i]);
		i++;
	}
	new[i] = '\0';
	return (new);
}
