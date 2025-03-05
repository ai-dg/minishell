/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: calbor-p <calbor-p@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/17 13:04:59 by calbor-p          #+#    #+#             */
/*   Updated: 2024/02/10 21:59:43 by calbor-p         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "string.h"

/*
Alloue (avec malloc(3)) et retourne une chaine de caractères
“fraiche” terminée par un ’\0’ représentant l’entier n passé
en paramètre. Les nombres négatifs doivent être gérés. Si l’al-
location échoue, la fonction renvoie NULL.
L’entier à convertir en une chaine de caractère
*/

static char	*get_strnbr(long nb, long div, int count, char *nbr)
{
	long	tmp;
	int		i;

	i = 0;
	tmp = nb;
	if (nbr[0] && nbr[0] == '-')
		i++;
	while (i < count)
	{
		tmp = (nb / div);
		nb = nb - (tmp * div);
		nbr[i++] = tmp + '0';
		if (div != 1)
			div /= 10;
	}
	nbr[i] = '\0';
	return (nbr);
}

static int	get_max_div(long nbr, long div, int *count)
{
	while (nbr > 9)
	{
		nbr /= 10;
		div *= 10;
		*count = *count + 1;
	}
	return (div);
}

char	*ft_itoa(int n)
{
	char	*nbr;
	int		count;
	long	div;
	long	nb;
	int		i;

	i = 0;
	count = 1;
	div = 1;
	nb = (long)n;
	if (n < 0)
	{
		nb = -nb;
		count++;
	}
	div = get_max_div(nb, div, &count);
	nbr = (char *)ft_calloc((size_t)count + 1, sizeof(char));
	if (!nbr)
		return (NULL);
	if (n < 0)
		nbr[i++] = '-';
	nbr = get_strnbr(nb, div, count, nbr);
	return (nbr);
}

/*
#include <limits.h>
#include <stdio.h>

int	main(void)
{
	printf("%d\n", INT_MIN);
	printf("%s\n", ft_itoa(INT_MIN));
}*/
