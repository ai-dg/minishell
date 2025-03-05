/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_join_splitted.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: calbor-p <calbor-p@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/14 15:28:28 by calbor-p          #+#    #+#             */
/*   Updated: 2024/06/12 21:15:25 by calbor-p         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_join_splitted(char **splitted, char *separator)
{
	int		i;
	int		length;
	char	*joined;

	length = 0;
	i = 0;
	while (splitted[i])
	{
		length += ft_strlen(splitted[i]) + 1;
		i++;
	}
	joined = malloc(length + 1);
	if (!joined)
		return (NULL);
	joined[0] = '\0';
	i = 0;
	while (splitted[i])
	{
		ft_strcat(joined, splitted[i]);
		if (splitted[i + 1])
			ft_strcat(joined, separator);
		i++;
	}
	return (joined);
}
