/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_striteri.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: calbor-p <calbor-p@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/17 16:16:42 by calbor-p          #+#    #+#             */
/*   Updated: 2023/11/18 13:26:31 by calbor-p         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*
Applique la fonction f à chaque caractère de la chaine de
caractères passée en paramètre en précisant son index en pre-
mier argument. Chaque caractère est passé par adresse à la
fonction f afin de pouvoir être modifié si nécéssaire.
*/

void	ft_striteri(char *s, void (*f)(unsigned int, char *))
{
	unsigned int	i;
	unsigned int	size;

	if (!s || !f)
		return ;
	i = 0;
	size = (unsigned int)ft_strlen(s);
	while (i < size)
	{
		f(i, &s[i]);
		i++;
	}
}
